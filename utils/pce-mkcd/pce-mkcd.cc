/* pce-cd target .iso image builder.
 *
 * Copyright (c) 2023 Adrian Siekierka
 *
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE
 * file in the project root for the full text.
 */

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <ios>
#include <map>
#include <memory>
#include <optional>
#include <regex>
#include <string>
#include <vector>

#include "../common/elf-mos.h"
#include "../common/elf.h"

#include "../common/parg/parg.h"

// Program arguments, error handling.

#define P_ARG_HELP 'h'
#define P_ARG_QUIET 'q'
#define P_ARG_VERBOSE 'v'
#define P_ARG_ISO_OFFSET 128
#define P_ARG_ISO_NO_PAD_END 129
#define P_ARG_IPL 130

static struct parg_option long_options[] = {
    {"help", PARG_NOARG, 0, P_ARG_HELP},
    {"ipl", PARG_REQARG, 0, P_ARG_IPL},
    {"iso-no-pad-end", PARG_NOARG, 0, P_ARG_ISO_NO_PAD_END},
    {"iso-offset", PARG_REQARG, 0, P_ARG_ISO_OFFSET},
    {"quiet", PARG_NOARG, 0, P_ARG_QUIET},
    {"verbose", PARG_NOARG, 0, P_ARG_VERBOSE},
    {0, 0, 0, 0}};
static const char *short_options = "hqv";

static const char *long_option_descriptions[] = {
    "Print help information.",
    "Specify the path to the ipl.bin file (first CD sector).",
    "Disable ISO padding mandated by the CD-ROM specification.",
    "Offset at the beginning of the ISO, in sectors.",
    "Disable progress messages.",
    "Enable more verbose messages."};

uint32_t iso_offset_sectors = 0;
bool iso_pad = true;
typedef enum {
  VERBOSITY_QUIET = 0,
  VERBOSITY_INFO = 1,
  VERBOSITY_VERBOSE = 2
} verbosity_level;
verbosity_level verbosity = VERBOSITY_INFO;

static void log(verbosity_level log_verbosity, const char *msg, ...) {
  if (verbosity >= log_verbosity) {
    va_list ap;
    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
  }
}

static void error(int result, const char *msg, ...) {
  va_list ap;
  va_start(ap, msg);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, msg, ap);
  fprintf(stderr, "\n");
  exit(result);
}

// Vector utilities.

static uint8_t byte_at(const std::vector<char> &vec, size_t offset) {
  return (uint8_t)vec[offset];
}

static uint16_t short_at(const std::vector<char> &vec, size_t offset) {
  return (uint8_t)vec[offset] | ((uint8_t)vec[offset + 1] << 8);
}

static uint32_t int_at(const std::vector<char> &vec, size_t offset) {
  return (uint8_t)vec[offset] | ((uint8_t)vec[offset + 1] << 8) |
         ((uint8_t)vec[offset + 2] << 16) | ((uint8_t)vec[offset + 3] << 24);
}

static std::vector<unsigned char> vector_at(const std::vector<char> &vec,
                                            size_t offset, size_t size) {
  std::vector<unsigned char> sub(size);
  memcpy(&sub[0], &vec[offset], std::min(size, vec.size() - offset));
  return sub;
}

// String utilities.

static bool starts_with(const std::string &haystack, const std::string &needle,
                        bool case_sensitive = true) {
  return needle.size() <= haystack.size() &&
         std::equal(needle.cbegin(), needle.cend(), haystack.cbegin(),
                    [case_sensitive](unsigned char a, unsigned char b) {
                      return case_sensitive
                                 ? a == b
                                 : std::tolower(a) == std::tolower(b);
                    });
}

static bool ends_with(const std::string &haystack, const std::string &needle,
                      bool case_sensitive = true) {
  return needle.size() <= haystack.size() &&
         std::equal(needle.crbegin(), needle.crend(), haystack.crbegin(),
                    [case_sensitive](unsigned char a, unsigned char b) {
                      return case_sensitive
                                 ? a == b
                                 : std::tolower(a) == std::tolower(b);
                    });
}

// Disc building code - useful constants.

#define SECTOR_SIZE 2048
#define SECTORS_PER_SECOND 75

static const char cd_symbol_prefix[] = "__cd_";
static const char ipl_system[] = "PC Engine CD-ROM SYSTEM";
static const char ipl_copyright[] =
    "Copyright HUDSON SOFT / NEC Home Electronics,Ltd.";

// Disc building code.

static uint32_t bytes_to_sectors(uint32_t bytes) {
  return (bytes + SECTOR_SIZE - 1) / SECTOR_SIZE;
}

static void pad_stream_to_sector(std::ofstream &out, uint32_t bytes) {
  uint32_t pad = (SECTOR_SIZE - (bytes % SECTOR_SIZE));
  if (pad == SECTOR_SIZE)
    return;
  while (pad--)
    out << (uint8_t)0;
}

class Disc;

class DiscEntry {
public:
  DiscEntry(std::string name) : _name(name) {}

  std::string name(void) const { return _name; }
  uint32_t offset(void) const { return _offset; }
  void offset(uint32_t value) { _offset = value; }

  virtual void write(Disc &disc, std::ofstream &out) = 0;
  virtual uint32_t sectors(void) const = 0;
  virtual uint8_t bank_start(void) { return 0; }
  virtual uint8_t bank_end(void) { return 0; }
  virtual uint8_t bank_count(void) { return (sectors() + 3) / 4; }
  virtual bool hidden(void) { return false; }

  virtual void mark_ipl(void) {
    error(1, "Cannot turn \"%s\" into an initial program!", name().c_str());
  }

  virtual std::string symbol_name(void) {
    std::string symbol_name = name();
    while (starts_with(symbol_name, "../") ||
           starts_with(symbol_name, "..\\")) {
      symbol_name = symbol_name.substr(3);
    }
    std::transform(symbol_name.begin(), symbol_name.end(), symbol_name.begin(),
                   [](unsigned char c) {
                     return std::isalnum(c) ? std::tolower(c) : '_';
                   });
    return symbol_name;
  }

  virtual std::optional<uint32_t> resolve_symbol(const std::string &name) {
    return std::nullopt;
  }

private:
  std::string _name;
  uint32_t _offset;
};

static const std::function<bool(const std::string &, const std::string &)>
    longest_first_compare = [](const std::string &a, const std::string &b) {
      if (a.length() != b.length())
        return a.length() > b.length();
      return a < b;
    };

class PadDiscEntry : public DiscEntry {
public:
  PadDiscEntry(std::string name, uint32_t sectors)
      : DiscEntry(name), _sectors(sectors) {}

  virtual bool hidden(void) { return true; }

  virtual void write(Disc &disc, std::ofstream &out) {
    char buffer[SECTOR_SIZE] = {0};
    for (auto i = 0; i < _sectors; i++) {
      out.write(buffer, SECTOR_SIZE);
    }
  }

  virtual uint32_t sectors(void) const { return _sectors; }

private:
  uint32_t _sectors;
};

class Disc {
public:
  Disc() : _symbols(longest_first_compare) {}

  uint32_t size(void) {
    DiscEntry *last = _entries.empty() ? nullptr : _entries.rbegin()->get();
    return last != nullptr ? last->offset() + last->sectors() : 0;
  }

  void add(std::shared_ptr<DiscEntry> ent) {
    if (!ent->hidden()) {
      std::string symbol_name = cd_symbol_prefix + ent->symbol_name() + "__";
      if (_symbols.find(symbol_name) != _symbols.end()) {
        error(1, "Symbol name prefix collision: %s (%s) != %s (%s)",
              symbol_name.c_str(), ent->name().c_str(), symbol_name.c_str(),
              _symbols.find(symbol_name)->second->name().c_str());
      }
      _symbols[symbol_name] = ent;
    }

    ent->offset(size());
    _entries.push_back(ent);
  }

  void finalize(void) {
    if (iso_pad) {
      // CD-ROM specification expects at least 2 seconds of trailing zeroes,
      // and at least 6 seconds of length total.
      uint32_t total_sectors = std::max(size(), 6U * SECTORS_PER_SECOND);
      uint32_t pad_sectors =
          std::max(total_sectors - size(), 2U * SECTORS_PER_SECOND);
      if (pad_sectors > 0) {
        log(VERBOSITY_VERBOSE,
            "Adding %d sectors of padding required by CD-ROM specification.",
            pad_sectors);
        add(std::make_shared<PadDiscEntry>(PadDiscEntry("pad", pad_sectors)));
      }
    }
  }

  void write(std::ofstream &out) {
    for (auto ent : _entries) {
      if (!ent->hidden()) {
        log(VERBOSITY_INFO, "Writing \"%s\" (%s%s) to ISO @ sector %d, size %d",
            ent->name().c_str(), cd_symbol_prefix, ent->symbol_name().c_str(),
            ent->offset(), ent->sectors());
      }
      out.seekp(ent->offset() * SECTOR_SIZE, std::ios::beg);
      ent->write(*this, out);
    }
    log(VERBOSITY_INFO, "Finished writing ISO, size %d", size());
  }

  auto entries() { return _entries; }
  auto symbols() { return _symbols; }

private:
  std::vector<std::shared_ptr<DiscEntry>> _entries;
  std::map<std::string, std::shared_ptr<DiscEntry>,
           decltype(longest_first_compare)>
      _symbols;
};

class ArrayDiscEntry : public DiscEntry {
public:
  ArrayDiscEntry(std::string name, std::vector<char> data)
      : DiscEntry(name), _data(data) {}

  virtual void write(Disc &disc, std::ofstream &out) {
    out.write(&_data[0], _data.size());
    pad_stream_to_sector(out, _data.size());
  }

  virtual uint32_t sectors(void) const {
    return bytes_to_sectors(_data.size());
  }

private:
  std::vector<char> _data;
};

class FileDiscEntry : public DiscEntry {
public:
  FileDiscEntry(std::string name) : DiscEntry(name) {
    _stream = std::ifstream(name, std::fstream::binary);
    _stream.seekg(0, std::ios::end);
    _length = _stream.tellg();
  }

  virtual void write(Disc &disc, std::ofstream &out) {
    char buffer[SECTOR_SIZE];
    uint32_t sectors_written = 0;

    _stream.seekg(0, std::ios::beg);
    do {
      _stream.read(buffer, SECTOR_SIZE);
      memset(buffer + _stream.gcount(), 0, SECTOR_SIZE - _stream.gcount());
      out.write(buffer, SECTOR_SIZE);
      sectors_written++;
    } while (_stream.gcount() > 0);

    assert(sectors_written == sectors());
  }

  virtual uint32_t sectors(void) const { return bytes_to_sectors(_length); }

private:
  std::ifstream _stream;
  uint32_t _length;
};

typedef enum { ELF_IPL_RAM, ELF_IPL_CARD, ELF_CARD } ElfMode;

class ElfDiscEntry : public DiscEntry {
public:
  ElfDiscEntry(std::string name) : DiscEntry(name) {
    std::ifstream stream(name, std::fstream::binary);
    elf_data = std::vector<char>((std::istreambuf_iterator<char>(stream)),
                                 std::istreambuf_iterator<char>());

    // Parse ELF header.
    if (!memcpy(&elf_data[EI_MAG0], ELFMAG, 4)) {
      error(1, "Not a valid ELF file!");
    } else if (byte_at(elf_data, EI_CLASS) != ELFCLASS32) {
      error(1, "Not a 32-bit ELF file!");
    } else if (byte_at(elf_data, EI_DATA) != ELFDATA2LSB) {
      error(1, "Not a little-endian ELF file!");
    } else if (short_at(elf_data, ELF32_EHDR_MACHINE) != EM_MOS) {
      error(1, "Not a MOS architecture ELF file!");
    }

    phdr_offset = int_at(elf_data, ELF32_EHDR_PHOFF);
    phdr_count = short_at(elf_data, ELF32_EHDR_PHNUM);
    phdr_size = short_at(elf_data, ELF32_EHDR_PHENTSIZE);

    shdr_offset = int_at(elf_data, ELF32_EHDR_SHOFF);
    shdr_count = short_at(elf_data, ELF32_EHDR_SHNUM);
    shdr_size = short_at(elf_data, ELF32_EHDR_SHENTSIZE);

    // Figure out ELF card data size by examining the Program Header.
    card_address_low = -1;
    card_address_high = 0;

    for (auto i = 0; i < phdr_count; i++) {
      uint32_t phdr = phdr_offset + (phdr_size * i);
      if (int_at(elf_data, phdr + ELF32_PHDR_TYPE) == PT_LOAD) {
        uint32_t filesz = int_at(elf_data, phdr + ELF32_PHDR_FILESZ);
        if (!filesz) {
          // Skip PHDR sections which do not contain any data.
          continue;
        }
        uint32_t memsz = int_at(elf_data, phdr + ELF32_PHDR_MEMSZ);
        uint32_t low = int_at(elf_data, phdr + ELF32_PHDR_PADDR);
        uint32_t high = low + memsz - 1;

        if (memsz > 0x2000) {
          error(1, "Section at %08X larger than one MPR bank!", low);
        }
        card_address_low = std::min(card_address_low, low);
        card_address_high = std::max(card_address_high, high);
      }
    }

    if (card_address_low >= 0x00f83000 && card_address_high < 0x00f83800) {
      // Valid configuration - IPL RAM upload.
      elf_mode = ELF_IPL_RAM;
      card_address_low = 0x00f83000;
      card_address_high = 0x00f83800;
    } else if (card_address_low >= 0x01680000 &&
               card_address_high < 0x01880000) {
      // Valid configuration - System Card upload.
      elf_mode = ELF_CARD;
      // Start at the beginning of an MPR bank.
      card_address_low &= ~0x1FFF;
    } else {
      error(1,
            "Don't know how to convert ELF file \"%s\" (%08X - %08X) into "
            "binary file!",
            name.c_str(), card_address_low, card_address_high);
    }

    // Locate the symbol and string tables.
    for (auto i = 0; i < shdr_count; i++) {
      uint32_t shdr = shdr_offset + (shdr_size * i);
      switch (int_at(elf_data, shdr + ELF32_SHDR_TYPE)) {
      case SHT_STRTAB: {
        strtab_offset = int_at(elf_data, shdr + ELF32_SHDR_OFFSET);
        strtab_size = int_at(elf_data, shdr + ELF32_SHDR_SIZE);
      } break;
      case SHT_SYMTAB: {
        symtab_offset = int_at(elf_data, shdr + ELF32_SHDR_OFFSET);
        symtab_size = int_at(elf_data, shdr + ELF32_SHDR_ENTSIZE);
        symtab_count = int_at(elf_data, shdr + ELF32_SHDR_SIZE);
        if (symtab_count == 0 || symtab_size == 0 ||
            (symtab_count % symtab_size) != 0) {
          error(1, "Unsupported layout of .symtab!");
        }
        symtab_count /= symtab_size;
      } break;
      }
    }
  }

  virtual void write(Disc &disc, std::ofstream &out) override {
    std::vector<char> data(sectors() * SECTOR_SIZE);
    uint8_t mpr_mapping[5] = {0, 1, 2, 3, 4};
    size_t start = out.tellp();

    memset(&data[0], 0, data.size());

    // Read Phdr contents.
    for (auto i = 0; i < phdr_count; i++) {
      uint32_t phdr = phdr_offset + (phdr_size * i);
      if (int_at(elf_data, phdr + ELF32_PHDR_TYPE) == PT_LOAD) {
        uint32_t offset = int_at(elf_data, phdr + ELF32_PHDR_OFFSET);
        uint32_t filesz = int_at(elf_data, phdr + ELF32_PHDR_FILESZ);
        if (!filesz) {
          continue;
        }
        uint32_t addr = int_at(elf_data, phdr + ELF32_PHDR_PADDR);
        uint32_t file_offset = addr_to_file_offset(addr);
        memcpy(&data[file_offset], &elf_data[offset], filesz);

        uint8_t mpr_bank = (addr >> 16) & 0xFF;
        uint8_t mpr_index = (addr >> 13) & 0x7;
        if (mpr_index >= 2 && mpr_index <= 6 && mpr_bank >= 0x80 &&
            mpr_bank <= 0x87) {
          mpr_mapping[mpr_index - 2] = mpr_bank - 0x80;
        }
      }
    }

    // Apply Rela contents.
    for (auto i = 0; i < shdr_count; i++) {
      uint32_t shdr = shdr_offset + (shdr_size * i);
      if (int_at(elf_data, shdr + ELF32_SHDR_TYPE) == SHT_RELA) {
        uint32_t rela_offset = int_at(elf_data, shdr + ELF32_SHDR_OFFSET);
        uint32_t rela_size = int_at(elf_data, shdr + ELF32_SHDR_ENTSIZE);
        uint32_t rela_count = int_at(elf_data, shdr + ELF32_SHDR_SIZE);
        for (auto j = 0; j < rela_count; j += rela_size) {
          uint32_t rela = rela_offset + j;
          uint32_t r_addr = int_at(elf_data, rela + ELF32_RELA_OFFSET);
          uint32_t r_file_offset = addr_to_file_offset(r_addr);
          uint32_t r_sym_index =
              ELF32_R_SYM(int_at(elf_data, rela + ELF32_RELA_INFO));
          uint32_t r_sym_type =
              ELF32_R_TYPE(int_at(elf_data, rela + ELF32_RELA_INFO));
          uint32_t r_sym = symtab_offset + r_sym_index * symtab_size;
          std::string r_sym_name =
              strtab_name(int_at(elf_data, r_sym + ELF32_SYM_NAME));
          uint32_t r_sym_value = int_at(elf_data, r_sym + ELF32_SYM_VALUE);
          uint16_t r_sym_shndx = short_at(elf_data, r_sym + ELF32_SYM_SHNDX);

          // All resolved symbols are relocated - look only for unresolved
          // symbols.
          if (starts_with(r_sym_name, cd_symbol_prefix)) {
            bool found = false;
            for (auto entry : disc.symbols()) {
              if (starts_with(r_sym_name, entry.first)) {
                auto r_disc_entry = entry.second;
                auto r_sym_subname = r_sym_name.substr(entry.first.length());
                uint32_t value = 0;

                if (starts_with(r_sym_subname, "sym_")) {
                  auto r_sym_other = r_sym_subname.substr(4);
                  auto r_sym_other_value =
                      r_disc_entry->resolve_symbol(r_sym_other);
                  if (r_sym_other_value.has_value()) {
                    value = r_sym_other_value.value();
                  } else {
                    error(1, "Could not locate symbol \"%s\" (%s).",
                          r_sym_other.c_str(), r_sym_name.c_str());
                  }
                } else if (r_sym_subname == "sector") {
                  value = entry.second->offset();
                } else if (r_sym_subname == "sector_count") {
                  value = entry.second->sectors();
                } else if (r_sym_subname == "bank_start") {
                  value = entry.second->bank_start();
                } else if (r_sym_subname == "bank_end") {
                  value = entry.second->bank_end();
                } else if (r_sym_subname == "bank_count") {
                  value = entry.second->bank_count();
                } else {
                  error(1, "Could not resolve CD symbol \"%s\"!",
                        r_sym_name.c_str());
                }

                // The user may specify a __cd_ symbol as an immediate or as
                // an address. Other relocation types are not supported, such
                // as PCREL or ASCIIZ.
                int width = 0;
                switch (r_sym_type) {
                case R_MOS_IMM8:
                  width = 1;
                  break;
                case R_MOS_ADDR8:
                  width = 1;
                  break;
                case R_MOS_ADDR16:
                  width = 2;
                  break;
                case R_MOS_ADDR16_LO:
                  width = 1;
                  break;
                case R_MOS_ADDR16_HI:
                  width = 1;
                  value >>= 8;
                  break;
                case R_MOS_ADDR24:
                  width = 3;
                  break;
                case R_MOS_ADDR24_BANK:
                  width = 1;
                  value >>= 16;
                  break;
                case R_MOS_ADDR24_SEGMENT:
                  width = 2;
                  break;
                case R_MOS_ADDR24_SEGMENT_LO:
                  width = 1;
                  break;
                case R_MOS_ADDR24_SEGMENT_HI:
                  width = 1;
                  value >>= 8;
                  break;
                case R_MOS_FK_DATA_4:
                  width = 4;
                  break;
                case R_MOS_FK_DATA_8:
                  width = 8;
                  break;
                case R_MOS_IMM16:
                  width = 2;
                  break;
                default:
                  error(1, "Unsupported relocation type %d!", r_sym_type);
                }
                log(VERBOSITY_VERBOSE, "=> Relocating \"%s\" @ %08X => %X",
                    r_sym_name.c_str(), r_addr, value);

                uint8_t carry = 0;
                for (auto x = 0; x < width; x++, value >>= 8) {
                  uint16_t sum = ((uint8_t)data[r_file_offset + x]) +
                                 (value & 0xFF) + carry;
                  carry = (sum >> 8);
                  data[r_file_offset + x] = sum;
                }

                found = true;
                break;
              }
            }

            if (!found) {
              error(1, "Could not locate file for CD symbol \"%s\"!",
                    r_sym_name.c_str());
            }
          }
        }
      }
    }

    // Write Phdr contents.
    out.seekp(start, std::ios::beg);
    out.write(&data[0], data.size());

    // Write IPL data.
    if (should_write_ipl()) {
      char buffer[32] = {0};
      out.seekp(start, std::ios::beg);
      if (elf_mode == ELF_IPL_RAM) {
        auto start_address =
            resolve_symbol("_start").value_or(card_address_low) & 0x7FF;
        buffer[6] = start_address; // code sector jump address
        buffer[7] = start_address >> 8;
      } else {
        uint32_t code_sector = iso_offset_sectors + offset() + 1;
        buffer[0] = code_sector >> 16;
        buffer[1] = code_sector >> 8;
        buffer[2] = code_sector;
        buffer[3] = (sectors() - 1);  // code sector count
        buffer[4] = card_address_low; // code sector load address
        buffer[5] = card_address_low >> 8;
        auto start_address =
            resolve_symbol("_start").value_or(card_address_low);
        buffer[6] = start_address; // code sector jump address
        buffer[7] = start_address >> 8;
      }
      memcpy(buffer + 8, mpr_mapping, 5);

      // TODO: ADPCM, VRAM graphics support.
      out.write(buffer, 32);

      // System name/Copyright notice - required by boot verification code.
      out.write(ipl_system, sizeof(ipl_system));
      out.write(ipl_copyright, sizeof(ipl_copyright));

      // TODO: Program name.
    }
  }

  virtual uint32_t sectors(void) const override {
    if (elf_mode == ELF_IPL_RAM) {
      return 1;
    } else {
      uint16_t diff_banks =
          (card_address_high >> 16) - (card_address_low >> 16);
      uint16_t diff_addresses =
          ((card_address_high & 0x1FFF) / SECTOR_SIZE) + 1;
      uint16_t diff_sectors =
          diff_banks * (8192 / SECTOR_SIZE) + diff_addresses;
      if (should_prepend_ipl()) {
        diff_sectors++;
      }
      return diff_sectors;
    }
  }

  virtual void mark_ipl(void) override {
    if (elf_mode == ELF_CARD) {
      elf_mode = ELF_IPL_CARD;
    }
  }

  virtual std::optional<uint32_t>
  resolve_symbol(const std::string &name) override {
    for (auto i = 0; i < symtab_count; i++) {
      uint32_t sym = symtab_offset + (symtab_size * i);
      std::string sym_name =
          strtab_name(int_at(elf_data, sym + ELF32_SYM_NAME));
      uint32_t sym_value = int_at(elf_data, sym + ELF32_SYM_VALUE);
      uint16_t sym_shndx = short_at(elf_data, sym + ELF32_SYM_SHNDX);
      if (sym_name == name && sym_shndx == SHN_ABS) {
        return sym_value;
      }
    }
    return DiscEntry::resolve_symbol(name);
  }

  virtual uint8_t bank_start(void) override { return (card_address_low >> 16); }

  virtual uint8_t bank_end(void) override { return (card_address_high >> 16); }

private:
  bool should_prepend_ipl(void) const { return elf_mode == ELF_IPL_CARD; }

  bool should_write_ipl(void) const {
    return elf_mode == ELF_IPL_RAM || elf_mode == ELF_IPL_CARD;
  }

  std::string strtab_name(uint32_t index) {
    if (index >= strtab_size) {
      error(1, "ELF file error: strtab index out of range: %d", index);
    }
    uint32_t location = strtab_offset + index;
    return std::string(&elf_data[location]);
  }

  uint32_t addr_to_file_offset(uint32_t addr) {
    if (addr < card_address_low || addr > card_address_high) {
      error(1, "File address %08X out of range (%08X - %08X)", addr,
            card_address_low, card_address_high);
    }
    addr -= card_address_low;
    return ((addr >> 16) * 0x2000) + (addr & 0x1FFF) +
           (should_prepend_ipl() ? SECTOR_SIZE : 0x0);
  }

  ElfMode elf_mode;
  std::vector<char> elf_data;
  uint32_t card_address_low, card_address_high;
  uint32_t phdr_offset, phdr_count, phdr_size;
  uint32_t shdr_offset, shdr_count, shdr_size;
  uint32_t symtab_offset, symtab_count, symtab_size;
  uint32_t strtab_offset, strtab_size;
};

static const std::string elf_ext = ".elf";

static bool try_append_ipl(Disc &disc, std::string name) {
  std::vector<char> buffer(2048);
  std::ifstream file(name, std::ios_base::binary);
  if (!file.good())
    return false;
  file.read(&buffer[0], SECTOR_SIZE);
  if (file.gcount() != SECTOR_SIZE)
    return false;

  disc.add(
      std::make_shared<ArrayDiscEntry>(ArrayDiscEntry("sector_0", buffer)));
  return true;
}

static void add_file(Disc &disc, std::string filename) {
  std::shared_ptr<DiscEntry> ptr;

  if (ends_with(filename, ".elf", false)) {
    ptr = std::make_shared<ElfDiscEntry>(ElfDiscEntry(filename));
  } else {
    ptr = std::make_shared<FileDiscEntry>(FileDiscEntry(filename));
  }
  if (disc.entries().size() == 1) {
    ptr->mark_ipl();
  }

  disc.add(ptr);
}

static void usage(int return_code) {
  if (return_code == 0) {
    printf("pce-mkcd - create ISO image for pce-cd target\n\n");
  }
  printf("Usage: pce-mkcd <output.iso> <files...>\n\nOptions:\n");
  const struct parg_option *option = long_options;
  const char **description = long_option_descriptions;
  while (option->name != nullptr) {
    printf("  ");
    if (isalnum(option->val))
      printf("-%c, ", option->val);
    printf("--%s", option->name);
    if (option->has_arg == PARG_REQARG)
      printf(" <arg>");
    if (option->has_arg == PARG_OPTARG)
      printf(" [arg]");
    printf("    %s\n", *description);
    option++;
    description++;
  }
  exit(return_code);
}

int main(int argc, char **argv) {
  struct parg_state ps;
  std::string ipl_path = "ipl.bin";
  Disc disc;

  parg_init(&ps);
  int optend = parg_reorder(argc, argv, short_options, long_options);

  int optval;
  while ((optval = parg_getopt_long(&ps, optend, argv, short_options,
                                    long_options, nullptr)) != -1) {
    switch (optval) {
    case P_ARG_HELP:
      usage(0);
      break;
    case P_ARG_IPL:
      ipl_path = ps.optarg;
      break;
    case P_ARG_ISO_NO_PAD_END:
      iso_pad = false;
      break;
    case P_ARG_ISO_OFFSET:
      iso_offset_sectors = atoi(ps.optarg);
      break;
    case P_ARG_QUIET:
      verbosity = VERBOSITY_QUIET;
      break;
    case P_ARG_VERBOSE:
      verbosity = VERBOSITY_VERBOSE;
      break;
    }
  }

  if ((argc - optend) < 2) {
    usage(1);
  }

  if (!try_append_ipl(disc, ipl_path)) {
    error(1, "Could not locate 'ipl.bin' file!");
  }

  for (int i = optend + 1; i < argc; i++) {
    if (argv[i][0] == '@') {
      std::ifstream list(argv[i] + 1);
      if (list.is_open()) {
        std::string line;
        while (std::getline(list, line)) {
          if (!starts_with(line, "#")) {
            add_file(disc, line);
          }
        }
      }
    } else {
      add_file(disc, argv[i]);
    }
  }

  if (disc.entries().size() < 2) {
    log(VERBOSITY_QUIET, "No files provided!");
    usage(1);
  }

  disc.finalize();

  std::ofstream outf(argv[optend], std::ios_base::binary);
  if (!outf.good()) {
    error(1, "Error opening \"%s\" for writing.", argv[1]);
  }
  disc.write(outf);

  return 0;
}
