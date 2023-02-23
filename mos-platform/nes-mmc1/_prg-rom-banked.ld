INPUT(reset.o)

__prg_rom_0_lma     = 0x008000;
__prg_rom_1_lma     = 0x018000;
__prg_rom_2_lma     = 0x028000;
__prg_rom_3_lma     = 0x038000;
__prg_rom_4_lma     = 0x048000;
__prg_rom_5_lma     = 0x058000;
__prg_rom_6_lma     = 0x068000;
__prg_rom_7_lma     = 0x078000;
__prg_rom_8_lma     = 0x088000;
__prg_rom_9_lma     = 0x098000;
__prg_rom_10_lma    = 0x0a8000;
__prg_rom_11_lma    = 0x0b8000;
__prg_rom_12_lma    = 0x0c8000;
__prg_rom_13_lma    = 0x0d8000;
__prg_rom_14_lma    = 0x0e8000;
__prg_rom_fixed_lma = 0xc000;

__prg_rom_0_offset     = 0x00000;
__prg_rom_1_offset     = 0x04000;
__prg_rom_2_offset     = 0x08000;
__prg_rom_3_offset     = 0x0c000;
__prg_rom_4_offset     = 0x10000;
__prg_rom_5_offset     = 0x14000;
__prg_rom_6_offset     = 0x18000;
__prg_rom_7_offset     = 0x1c000;
__prg_rom_8_offset     = 0x20000;
__prg_rom_9_offset     = 0x24000;
__prg_rom_10_offset    = 0x28000;
__prg_rom_11_offset    = 0x2c000;
__prg_rom_12_offset    = 0x30000;
__prg_rom_13_offset    = 0x34000;
__prg_rom_14_offset    = 0x38000;
__prg_rom_fixed_offset = __prg_rom_size * 1024 - 0x4000;

MEMORY {
  /* PRG-ROM LMAs. */
  prg_rom_0     : ORIGIN = __prg_rom_0_lma,     LENGTH = __prg_rom_size >= 32  ? 0x4000 - 12 : 0
  prg_rom_1     : ORIGIN = __prg_rom_1_lma,     LENGTH = __prg_rom_size >= 64  ? 0x4000 - 12 : 0
  prg_rom_2     : ORIGIN = __prg_rom_2_lma,     LENGTH = __prg_rom_size >= 64  ? 0x4000 - 12 : 0
  prg_rom_3     : ORIGIN = __prg_rom_3_lma,     LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_4     : ORIGIN = __prg_rom_4_lma,     LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_5     : ORIGIN = __prg_rom_5_lma,     LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_6     : ORIGIN = __prg_rom_6_lma,     LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_7     : ORIGIN = __prg_rom_7_lma,     LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_8     : ORIGIN = __prg_rom_8_lma,     LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_9     : ORIGIN = __prg_rom_9_lma,     LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_10    : ORIGIN = __prg_rom_10_lma,    LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_11    : ORIGIN = __prg_rom_11_lma,    LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_12    : ORIGIN = __prg_rom_12_lma,    LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_13    : ORIGIN = __prg_rom_13_lma,    LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_14    : ORIGIN = __prg_rom_14_lma,    LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_fixed : ORIGIN = __prg_rom_fixed_lma, LENGTH = 0x4000 - 12

  /* Reset stub. Arbitrarily put its VMA in the first bank. */
  reset : ORIGIN = 0x20000 - 12, LENGTH = 12

  /* Reset stub for the fixed bank. */
  reset_fixed : ORIGIN = 0x10000 - 12, LENGTH = 12
}

REGION_ALIAS("c_rom", prg_rom_fixed)

SECTIONS {
  .prg_rom_0     : { *(.prg_rom_0     .prg_rom_0.*)     } >prg_rom_0
  .prg_rom_1     : { *(.prg_rom_1     .prg_rom_1.*)     } >prg_rom_1
  .prg_rom_2     : { *(.prg_rom_2     .prg_rom_2.*)     } >prg_rom_2
  .prg_rom_3     : { *(.prg_rom_3     .prg_rom_3.*)     } >prg_rom_3
  .prg_rom_4     : { *(.prg_rom_4     .prg_rom_4.*)     } >prg_rom_4
  .prg_rom_5     : { *(.prg_rom_5     .prg_rom_5.*)     } >prg_rom_5
  .prg_rom_6     : { *(.prg_rom_6     .prg_rom_6.*)     } >prg_rom_6
  .prg_rom_7     : { *(.prg_rom_7     .prg_rom_7.*)     } >prg_rom_7
  .prg_rom_8     : { *(.prg_rom_8     .prg_rom_8.*)     } >prg_rom_8
  .prg_rom_9     : { *(.prg_rom_9     .prg_rom_9.*)     } >prg_rom_9
  .prg_rom_10    : { *(.prg_rom_10    .prg_rom_10.*)    } >prg_rom_10
  .prg_rom_11    : { *(.prg_rom_11    .prg_rom_11.*)    } >prg_rom_11
  .prg_rom_12    : { *(.prg_rom_12    .prg_rom_12.*)    } >prg_rom_12
  .prg_rom_13    : { *(.prg_rom_13    .prg_rom_13.*)    } >prg_rom_13
  .prg_rom_14    : { *(.prg_rom_14    .prg_rom_14.*)    } >prg_rom_14
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed
}

INCLUDE dpcm.ld

SECTIONS {
  .reset       : { KEEP(*(.reset))       } >reset
  .reset_fixed : { KEEP(*(.reset_fixed)) } >reset_fixed
}
