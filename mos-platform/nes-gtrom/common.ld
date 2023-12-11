/* NES-GTROM iNES file linker script. */

INCLUDE nes.ld

ASSERT(__prg_rom_size <= 512, "GTROM only supports up to 512 KiB of PRG.")

ASSERT(__chr_ram_size + __chr_nvram_size <= 16,
       "GTROM only supports up to 16 KiB of CHR-(NV)RAM.")

ASSERT(__prg_ram_size == 0, "GTROM does not support PRG-RAM")
ASSERT(__prg_nvram_size == 0, "GTROM does not support PRG-NVRAM")
