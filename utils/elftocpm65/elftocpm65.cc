/* Converts ELF files produced by llvm-mos into CP/M-65 relocatable
 * executables.  Note that you _have_ to use the .ld file provided; it won't
 * work on arbitrary ELF files.
 *
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license. See the LICENSE file in the project
 * root for the full text.
 */

#include "elf.h"
#include <fstream>
#include <regex>
#include <set>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <vector>

/* MOS relocations (at least, the ones we care about). */

#define R_MOS_ADDR8 2
#define R_MOS_ADDR16 3
#define R_MOS_ADDR16_LO 4
#define R_MOS_ADDR16_HI 5

/* ELF structure definitions. */

#define ELF32_EHDR_IDENT offsetof(Elf32_Ehdr, e_ident)
#define ELF32_EHDR_PHENTSIZE offsetof(Elf32_Ehdr, e_phentsize)
#define ELF32_EHDR_PHNUM offsetof(Elf32_Ehdr, e_phnum)
#define ELF32_EHDR_PHOFF offsetof(Elf32_Ehdr, e_phoff)

#define ELF32_PHDR_TYPE offsetof(Elf32_Phdr, p_type)
#define ELF32_PHDR_FILESZ offsetof(Elf32_Phdr, p_filesz)
#define ELF32_PHDR_OFFSET offsetof(Elf32_Phdr, p_offset)
#define ELF32_PHDR_PADDR offsetof(Elf32_Phdr, p_paddr)
#define ELF32_PHDR_VADDR offsetof(Elf32_Phdr, p_vaddr)
#define ELF32_PHDR__SIZE sizeof(Elf32_Phdr)

#define ELF32_SYM_VALUE offsetof(Elf32_Sym, st_value)
#define ELF32_SYM__SIZE sizeof(Elf32_Sym)

#define ELF32_RELA_INFO offsetof(Elf32_Rela, r_info)
#define ELF32_RELA_OFFSET offsetof(Elf32_Rela, r_offset)
#define ELF32_RELA__SIZE sizeof(Elf32_Rela)

static std::string outputFilename;
static std::string inputFilename;
static std::fstream outputFile;

static void error(const char *msg, ...) {
  va_list ap;
  va_start(ap, msg);
  fprintf(stderr, "error: ");
  vfprintf(stderr, msg, ap);
  fputc('\n', stderr);
  exit(1);
}

static void syntaxError() {
  error("syntax: elftocpm65 <elffile> [<binaryfile>]");
}

static void parseArguments(int argc, char *const *argv) {
  if (argc == 2) {
    inputFilename = argv[1];
    outputFilename =
        std::regex_replace(inputFilename, std::regex("\\.elf$"), "");
  } else {
    inputFilename = argv[1];
    outputFilename = argv[2];
  }
}

class Elf {
public:
  Elf(const std::string &filename) {
    std::ifstream is(filename.c_str(),
                     std::fstream::out | std::fstream::binary);

    if (!is)
      error("cannot open input file: %s", strerror(errno));

    _bytes = std::vector<char>((std::istreambuf_iterator<char>(is)),
                               std::istreambuf_iterator<char>());

    auto ident = arrayAt(ELF32_EHDR_IDENT, 16);
    if ((ident[EI_MAG0] != ELFMAG0) || (ident[EI_MAG1] != ELFMAG1) ||
        (ident[EI_MAG2] != ELFMAG2) || (ident[EI_MAG3] != ELFMAG3) ||
        (ident[EI_CLASS] != ELFCLASS32) || (ident[EI_DATA] != ELFDATA2LSB))
      error("not a little-endian ELF32 file");

    if (wordAt(ELF32_EHDR_PHENTSIZE) != 32)
      error("unsupported PHDR size");
    _phoff = longAt(ELF32_EHDR_PHOFF);
    _phnum = wordAt(ELF32_EHDR_PHNUM);
  }

  uint8_t byteAt(uint32_t offset) { return _bytes.at(offset); }

  uint16_t wordAt(uint32_t offset) {
    return byteAt(offset) | (byteAt(offset + 1) << 8);
  }

  uint32_t longAt(uint32_t offset) {
    return wordAt(offset) | (wordAt(offset + 2) << 16);
  }

  std::vector<uint8_t> arrayAt(uint32_t offset, uint32_t length) {
    std::vector<uint8_t> result(length);
    for (unsigned i = 0; i < length; i++)
      result[i] = byteAt(offset + i);
    return result;
  }

  uint32_t findPhdr(int index) const { return _phoff + index * 32; }

  int phdrCount() const { return _phnum; }

private:
  std::vector<char> _bytes;
  uint32_t _phoff;
  int _phnum;
};

std::vector<uint8_t> toBytestream(const std::set<uint16_t> &differences) {
  std::vector<uint8_t> bytes;
  uint16_t pos = 0;

  for (uint16_t diff : differences) {
    uint16_t delta = diff - pos;
    while (delta >= 0xe) {
      bytes.push_back(0xe);
      delta -= 0xe;
    }
    bytes.push_back(delta);

    pos = diff;
  }
  bytes.push_back(0xf);

  std::vector<uint8_t> results;
  for (int i = 0; i < bytes.size(); i += 2) {
    uint8_t left = bytes[i];
    uint8_t right = ((i + 1) < bytes.size()) ? bytes[i + 1] : 0x00;
    results.push_back((left << 4) | right);
  }
  return results;
}

int main(int argc, char *const *argv) {
  parseArguments(argc, argv);
  if (inputFilename.empty() || outputFilename.empty())
    syntaxError();

  /* Open the input ELF file. */

  Elf elf(inputFilename);

  /* Open the output file. */

  outputFile.open(outputFilename, std::fstream::in | std::fstream::out |
                                      std::fstream::trunc |
                                      std::fstream::binary);
  if (!outputFile)
    error("cannot open output file: %s", strerror(errno));

  /* Fetch the actual bytes. */

  std::vector<uint8_t> bytes;
  {
    auto append_phdr = [&](uint32_t off) {
      uint32_t codeOffset = elf.longAt(off + ELF32_PHDR_OFFSET);
      uint32_t targetAddress = elf.longAt(off + ELF32_PHDR_PADDR);
      uint32_t codeLen = elf.longAt(off + ELF32_PHDR_FILESZ);
      uint32_t currentLen = bytes.size();

      bytes.resize(
          std::max<uint32_t>(bytes.size(), targetAddress + codeLen - 0x200));
      for (int i = 0; i < codeLen; i++)
        bytes[targetAddress - 0x200 + i] = elf.byteAt(codeOffset + i);
    };

    for (int phdr = 0; phdr < elf.phdrCount(); phdr++)
    {
      uint32_t off = elf.findPhdr(phdr);
      if (elf.longAt(off + ELF32_PHDR_TYPE) == PT_LOAD)
        append_phdr(off);
    }
  }

  /* Accumulate relocations. */

  std::set<uint16_t> zpRelocations;
  std::set<uint16_t> memRelocations;
  memRelocations.insert(3); /* work around linker weirdness */

  /* Second-last phdr must contain the relocations. */

  uint32_t relaPhdr = elf.findPhdr(elf.phdrCount()-2);
  uint32_t relaCount =
      elf.longAt(relaPhdr + ELF32_PHDR_FILESZ) / ELF32_RELA__SIZE;
  uint32_t relaOffset = elf.longAt(relaPhdr + ELF32_PHDR_OFFSET);

  /* Last phdr must contain the symbol table. */

  uint32_t symbolPhdr = elf.findPhdr(elf.phdrCount()-1);
  uint32_t symbolCount =
      elf.longAt(symbolPhdr + ELF32_PHDR_FILESZ) / ELF32_SYM__SIZE;
  uint32_t symbolOffset = elf.longAt(symbolPhdr + ELF32_PHDR_OFFSET);

  for (unsigned i = 0; i < relaCount; i++) {
    uint32_t rela = relaOffset + i * ELF32_RELA__SIZE;
    uint32_t offset = elf.longAt(rela + ELF32_RELA_OFFSET) - 0x0200;
    unsigned symbolIndex = ELF32_R_SYM(elf.longAt(rela + ELF32_RELA_INFO));
    uint32_t symbol = symbolOffset + symbolIndex * ELF32_SYM__SIZE;
    uint32_t value = elf.longAt(symbol + ELF32_SYM_VALUE);

    if (value < 0x100) {
      /* Zero page address. */

      switch (ELF32_R_TYPE(elf.longAt(rela + ELF32_RELA_INFO))) {
      case R_MOS_ADDR8:
      case R_MOS_ADDR16:
      case R_MOS_ADDR16_LO:
        zpRelocations.insert(offset + 0);
        break;

      case R_MOS_ADDR16_HI:
        break;
      }
    } else {
      /* Normal address. */

      switch (ELF32_R_TYPE(elf.longAt(rela + ELF32_RELA_INFO))) {
      case R_MOS_ADDR8:
        error("8-bit reference to 16-bit address 0x%x at relo %d, address "
              "0x%x?",
              value, i, offset);
        break;

      case R_MOS_ADDR16:
        memRelocations.insert(offset + 1);
        break;

      case R_MOS_ADDR16_HI:
        memRelocations.insert(offset + 0);
        break;

      case R_MOS_ADDR16_LO:
        break;
      }
    }
  }

  /* Adjust memory relocations to remove the link offset. */

  for (uint16_t offset : memRelocations)
    bytes[offset] -= 2;

  /* Add the relocation tables. */

  for (uint8_t b : toBytestream(zpRelocations))
    bytes.push_back(b);
  for (uint8_t b : toBytestream(memRelocations))
    bytes.push_back(b);

  /* Adjust the memory requirements to ensure the relocations can be loaded.
   */

  bytes[1] = std::max<unsigned>(bytes[1], (bytes.size() + 255) / 256);

  /* Write the output file. */

  outputFile.write((const char *)&bytes[0], bytes.size());
  outputFile.close();

  return 0;
}

// vim: ts=2 sw=2 et
