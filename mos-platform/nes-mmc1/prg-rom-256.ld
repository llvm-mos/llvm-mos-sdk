INCLUDE _prg-rom-banked.ld

__prg_rom_size = 256;

SECTIONS {
  .reset_0  : OVERLAY { KEEP(*(.reset_0))  } >reset_0
  .reset_1  : OVERLAY { KEEP(*(.reset_1))  } >reset_1
  .reset_2  : OVERLAY { KEEP(*(.reset_2))  } >reset_2
  .reset_3  : OVERLAY { KEEP(*(.reset_3))  } >reset_3
  .reset_4  : OVERLAY { KEEP(*(.reset_4))  } >reset_4
  .reset_5  : OVERLAY { KEEP(*(.reset_5))  } >reset_5
  .reset_6  : OVERLAY { KEEP(*(.reset_6))  } >reset_6
  .reset_7  : OVERLAY { KEEP(*(.reset_7))  } >reset_7
  .reset_8  : OVERLAY { KEEP(*(.reset_8))  } >reset_8
  .reset_9  : OVERLAY { KEEP(*(.reset_9))  } >reset_9
  .reset_10 : OVERLAY { KEEP(*(.reset_10)) } >reset_10
  .reset_11 : OVERLAY { KEEP(*(.reset_11)) } >reset_11
  .reset_12 : OVERLAY { KEEP(*(.reset_12)) } >reset_12
  .reset_13 : OVERLAY { KEEP(*(.reset_13)) } >reset_13
  .reset_14 : OVERLAY { KEEP(*(.reset_14)) } >reset_14
}
