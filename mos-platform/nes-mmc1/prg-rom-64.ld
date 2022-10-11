INCLUDE _prg-rom-banked.ld

__prg_rom_size = 64;

SECTIONS {
  .reset_0 : OVERLAY { KEEP(*(.reset_0)) } >reset_0
  .reset_1 : OVERLAY { KEEP(*(.reset_1)) } >reset_1
  .reset_2 : OVERLAY { KEEP(*(.reset_2)) } >reset_2
}
