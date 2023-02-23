/**
 * This ensures that SIROM is set up correctly, since it leaves the MMC 1 hooked
 * up to the address lines, and it could thus boot in any banked PRG-ROM state.
 */

INCLUDE _prg-rom-banked.ld

__prg_rom_size = 32;

INPUT(init-prg-rom-32.o)

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)     FULL(reset)
  FULL(prg_rom_fixed) FULL(reset_fixed)
  FULL(chr_rom)
}
