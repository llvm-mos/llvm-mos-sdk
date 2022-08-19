INCLUDE _prg-rom-banked.ld

__prg_rom_size = 128;

REGION_ALIAS("c_rom_vma", prg_rom_7_vma)
REGION_ALIAS("c_rom_lma", prg_rom_7_lma)

SECTIONS {
  .reset_0 : OVERLAY { KEEP(*(.reset_0)) } >reset_0
  .reset_1 : OVERLAY { KEEP(*(.reset_1)) } >reset_1
  .reset_2 : OVERLAY { KEEP(*(.reset_2)) } >reset_2
  .reset_3 : OVERLAY { KEEP(*(.reset_3)) } >reset_3
  .reset_4 : OVERLAY { KEEP(*(.reset_4)) } >reset_4
  .reset_5 : OVERLAY { KEEP(*(.reset_5)) } >reset_5
  .reset_6 : OVERLAY { KEEP(*(.reset_6)) } >reset_6
  .reset_7 : OVERLAY { KEEP(*(.reset_last)) } >reset_7
}
