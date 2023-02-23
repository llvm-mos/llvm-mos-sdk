/* Common elements of NES-NROM iNES file linker scripts. */

INCLUDE nes.ld
INCLUDE prg-ram-fixed.ld
INCLUDE prg-rom-fixed.ld

ASSERT(__chr_rom_size <= 8, "NROM only supports up to 8 KiB of CHR-ROM.")
ASSERT(__chr_ram_size + __chr_nvram_size <= 8,
       "NROM only supports up to 8KiB of CHR-(NV)RAM.")
