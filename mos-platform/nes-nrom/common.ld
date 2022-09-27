/* Common elements of NES-NROM iNES file linker scripts. */

INCLUDE nes.ld
INCLUDE prg-ram-fixed.ld
INCLUDE prg-rom-fixed.ld

ASSERT(__chr_rom_size <= 8, "NROM only supports up to 8 KiB of CHR-ROM.")
ASSERT(__chr_rom_size == 0 || __chr_rom_size == 1 << LOG2CEIL(__chr_rom_size),
       "NROM only supports pow2 CHR-ROM sizes.")
ASSERT(__chr_ram_size + __chr_nvram_size <= 8,
       "NROM only supports up to 8KiB of CHR-(NV)RAM.")

SECTIONS {
  .chr_rom : { KEEP(*(.chr_rom .chr_rom.*)) } >chr_rom
}

INCLUDE ines.ld
