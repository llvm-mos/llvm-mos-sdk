/**
 * This ensures that SIROM is set up correctly, since it leaves the MMC 1 hooked
 * up to the address lines, and it could thus boot in any banked PRG-ROM state.
 */

INCLUDE _prg-rom-banked.ld

__prg_rom_size = 32;

INPUT(init-prg-rom-32-banked.o)

REGION_ALIAS("c_rom_vma", prg_rom_1_vma)
REGION_ALIAS("c_rom_lma", prg_rom_1_lma)

SECTIONS {
  .reset_0 : OVERLAY { KEEP(*(.reset_0)) } >reset_0
  .reset_1 : OVERLAY { KEEP(*(.reset_last)) } >reset_1
}
