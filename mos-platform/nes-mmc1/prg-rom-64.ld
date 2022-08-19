INCLUDE _prg-rom-banked.ld

__prg_rom_size = 64;

REGION_ALIAS("c_rom_vma", prg_rom_3_vma)
REGION_ALIAS("c_rom_lma", prg_rom_3_lma)

SECTIONS {
  .reset_0 : OVERLAY { KEEP(*(.reset_0)) } >reset_0
  .reset_1 : OVERLAY { KEEP(*(.reset_1)) } >reset_1
  .reset_2 : OVERLAY { KEEP(*(.reset_2)) } >reset_2
  .reset_3 : OVERLAY { KEEP(*(.reset_last)) } >reset_3
}
