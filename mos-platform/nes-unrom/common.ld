/* NES-UNROM iNES file linker script. */

INCLUDE nes.ld

ASSERT(__chr_rom_size <= 8, "UNROM only supports up to 8 KiB of CHR-ROM.")
ASSERT(__chr_ram_size + __chr_nvram_size <= 8,
       "UNROM only supports up to 8KiB of CHR-(NV)RAM.")

ASSERT(__prg_ram_size == 0,
       "UNROM does not support PRG RAM")
ASSERT(__prg_nvram_size == 0,
       "UNROM does not support PRG-NVRAM")
