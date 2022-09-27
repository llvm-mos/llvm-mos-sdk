#include <fcntl.h>
#include <unistd.h>
#include <fmt/format.h>
#include <libelf.h>
#include <string>
#include <fstream>
#include <vector>
#include <set>

/* MOS relocations (at least, the ones we care about). */

#define R_MOS_ADDR8	    2
#define R_MOS_ADDR16    3
#define R_MOS_ADDR16_LO 4
#define R_MOS_ADDR16_HI 5

static std::string outputFilename;
static std::string inputFilename;
static Elf* elf;
static Elf32_Ehdr* elfhdr;
static std::fstream outputFile;

template <typename... T>
void error(fmt::format_string<T...> fmt, T&&... args)
{
    fmt::print(stderr, "error: ");
    fmt::print(stderr, fmt, args...);
    fputc('\n', stderr);
    exit(1);
}

static void syntaxError()
{
    error("syntax: elftocpm65 <inputfile> -o <outputfile>");
}

static void parseArguments(int argc, char* const* argv)
{
    for (;;)
    {
        switch (getopt(argc, argv, "-o:"))
        {
            case -1:
                return;

            case 1:
                if (!inputFilename.empty())
                    error("you've already specified an input file");
                inputFilename = optarg;
                break;

            case 'o':
                if (!outputFilename.empty())
                    error("you've already specified an output file");
                outputFilename = optarg;
                break;

            default:
                syntaxError();
        }
    }
}

template <class T>
static std::vector<T*> getElfTable(uint32_t sh_type, Elf_Type d_type)
{
    std::vector<T*> results;

    Elf_Scn* section = nullptr;
    for (;;)
    {
        section = elf_nextscn(elf, section);
        if (!section)
            break;

        auto* shdr = elf32_getshdr(section);
        if (shdr->sh_type == sh_type)
        {
            Elf_Data* data = nullptr;
            for (;;)
            {
                data = elf_getdata(section, data);
                if (!data)
                    break;

                if (data->d_type != d_type)
                    error("bad ELF data type; got {:x}, wanted {:x}",
                        data->d_type, d_type);

                T* items = (T*) data->d_buf;
                int count = shdr->sh_size / shdr->sh_entsize;

                for (int i=0; i<count; i++)
                {
                    T* item = items + i;
                    results.push_back(item);
                }
            }
        }
    }

    return results;
}

std::vector<uint8_t> toBytestream(const std::set<uint16_t>& differences)
{
    std::vector<uint8_t> bytes;
    uint16_t pos = 0;

    for (uint16_t diff : differences)
    {
        uint16_t delta = diff - pos;
        while (delta >= 0xe)
        {
            bytes.push_back(0xe);
            delta -= 0xe;
        }
        bytes.push_back(delta);

        pos = diff;
    }
    bytes.push_back(0xf);

    std::vector<uint8_t> results;
    for (int i = 0; i < bytes.size(); i += 2)
    {
        uint8_t left = bytes[i];
        uint8_t right = ((i + 1) < bytes.size()) ? bytes[i + 1] : 0x00;
        results.push_back((left << 4) | right);
    }
    return results;
}

int main(int argc, char* const* argv)
{
    parseArguments(argc, argv);
    if (inputFilename.empty() || outputFilename.empty())
        syntaxError();

    /* Open the input ELF file. */

    int fd = open(inputFilename.c_str(), O_RDONLY);
    if (!fd)
        error("cannot open input file: {}", strerror(errno));

    elf_version(EV_NONE);
    if (elf_version(EV_CURRENT) == EV_NONE)
        error("libelf version mismatch");

    elf = elf_begin(fd, ELF_C_READ, nullptr);

    /* Validate the ELF file. */

    {
        char *ehdr_ident = NULL;
         ehdr_ident = elf_getident(elf, NULL);
         if (ehdr_ident[0] != '\x7f' ||
             ehdr_ident[1] != '\x45' ||  // 'E'
             ehdr_ident[2] != '\x4C' ||  // 'L'
             ehdr_ident[3] != '\x46')    // 'F'
            error("not a valid ELF file");
    }

    elfhdr = elf32_getehdr(elf);
    if (!elfhdr)
        error("not a 32-bit ELF file");

    /* Open the output file. */

    outputFile.open(outputFilename,
        std::fstream::in | std::fstream::out | std::fstream::trunc |
            std::fstream::binary);
    if (!outputFile)
        error("cannot open output file: {}", strerror(errno));

    /* Fetch the actual bytes. */

    std::vector<uint8_t> bytes;
    {
        Elf_Scn* section = nullptr;
        for (;;)
        {
            section = elf_nextscn(elf, section);
            if (!section)
                break;

            auto* shdr = elf32_getshdr(section);
            if ((shdr->sh_type == SHT_PROGBITS) && (shdr->sh_size != 0))
            {
                /* TODO: there should be a better way to detect comments. */
                std::string name = elf_strptr(elf, elfhdr->e_shstrndx, shdr->sh_name);
                if (name != ".comment")
                {
                    auto* data = elf_rawdata(section, nullptr);
                    const char* ptr = (const char*) data->d_buf;
                    uint32_t addr = shdr->sh_addr - 0x0200;
                    if (addr > 0x10000)
                        error("bad section address 0x{:x}", shdr->sh_addr);
                    size_t requiredSize = addr + data->d_size;

                    if (bytes.size() < requiredSize)
                        bytes.resize(requiredSize);

                    std::copy(ptr, ptr+data->d_size, bytes.begin() + addr);
                }
            }
        }
    }

    /* Accumulate relocations. */

    std::set<uint16_t> zpRelocations;
    std::set<uint16_t> memRelocations;
    memRelocations.insert(3); /* work around linker weirdness */
    auto symbols = getElfTable<Elf32_Sym>(SHT_SYMTAB, ELF_T_SYM);
    auto relocations = getElfTable<Elf32_Rela>(SHT_RELA, ELF_T_RELA);
    for (auto* rela : relocations)
    {
        Elf32_Sym* symbol = symbols.at(ELF32_R_SYM(rela->r_info));
        unsigned offset = rela->r_offset - 0x0200;
        if (symbol->st_shndx)
        {
            if (symbol->st_value < 0x100)
            {
                /* Zero page address. */

                switch (ELF32_R_TYPE(rela->r_info))
                {
                    case R_MOS_ADDR8:
                    case R_MOS_ADDR16:
                    case R_MOS_ADDR16_LO:
                        zpRelocations.insert(offset+0);
                        break;

                    case R_MOS_ADDR16_HI:
                        break;
                }
            }
            else
            {
                /* Normal address. */

                switch (ELF32_R_TYPE(rela->r_info))
                {
                    case R_MOS_ADDR8:
                        error("8-bit reference to 16-bit address?");
                        break;

                    case R_MOS_ADDR16:
                        memRelocations.insert(offset+1);
                        break;

                    case R_MOS_ADDR16_HI:
                        memRelocations.insert(offset+0);
                        break;

                    case R_MOS_ADDR16_LO:
                        break;
                }
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

    outputFile.write((const char*) &bytes[0], bytes.size());
    outputFile.close();
    return 0;
}

// vim: ts=4 sw=4 et

