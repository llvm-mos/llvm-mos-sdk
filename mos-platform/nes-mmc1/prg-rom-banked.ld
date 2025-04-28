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
__prg_rom_15_lma    = 0x0f8000;
__prg_rom_16_lma    = 0x108000;
__prg_rom_17_lma    = 0x118000;
__prg_rom_18_lma    = 0x128000;
__prg_rom_19_lma    = 0x138000;
__prg_rom_20_lma    = 0x148000;
__prg_rom_21_lma    = 0x158000;
__prg_rom_22_lma    = 0x168000;
__prg_rom_23_lma    = 0x178000;
__prg_rom_24_lma    = 0x188000;
__prg_rom_25_lma    = 0x198000;
__prg_rom_26_lma    = 0x1A8000;
__prg_rom_27_lma    = 0x1B8000;
__prg_rom_28_lma    = 0x1C8000;
__prg_rom_29_lma    = 0x1D8000;
__prg_rom_30_lma    = 0x1E8000;
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
__prg_rom_15_offset    = 0x3C000;
__prg_rom_16_offset    = 0x40000;
__prg_rom_17_offset    = 0x44000;
__prg_rom_18_offset    = 0x48000;
__prg_rom_19_offset    = 0x4c000;
__prg_rom_20_offset    = 0x50000;
__prg_rom_21_offset    = 0x54000;
__prg_rom_22_offset    = 0x58000;
__prg_rom_23_offset    = 0x5c000;
__prg_rom_24_offset    = 0x60000;
__prg_rom_25_offset    = 0x64000;
__prg_rom_26_offset    = 0x68000;
__prg_rom_27_offset    = 0x6c000;
__prg_rom_28_offset    = 0x70000;
__prg_rom_29_offset    = 0x74000;
__prg_rom_30_offset    = 0x78000;
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
  prg_rom_15    : ORIGIN = __prg_rom_15_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_16    : ORIGIN = __prg_rom_16_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_17    : ORIGIN = __prg_rom_17_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_18    : ORIGIN = __prg_rom_18_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_19    : ORIGIN = __prg_rom_19_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_20    : ORIGIN = __prg_rom_20_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_21    : ORIGIN = __prg_rom_21_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_22    : ORIGIN = __prg_rom_22_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_23    : ORIGIN = __prg_rom_23_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_24    : ORIGIN = __prg_rom_24_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_25    : ORIGIN = __prg_rom_25_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_26    : ORIGIN = __prg_rom_26_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_27    : ORIGIN = __prg_rom_27_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_28    : ORIGIN = __prg_rom_28_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_29    : ORIGIN = __prg_rom_29_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_30    : ORIGIN = __prg_rom_30_lma,    LENGTH = __prg_rom_size >= 512 ? 0x4000 - 12 : 0
  prg_rom_fixed : ORIGIN = __prg_rom_fixed_lma, LENGTH = 0x4000 - 12

  /* Reset stub. Arbitrarily put its VMA in the first bank. */
  reset : ORIGIN = 0x20000 - 12, LENGTH = 12

  /* Reset stub for the fixed bank. */
  reset_fixed : ORIGIN = 0x10000 - 12, LENGTH = 12
}

REGION_ALIAS("c_readonly", prg_rom_fixed)

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
  .prg_rom_15    : { *(.prg_rom_15    .prg_rom_15.*)    } >prg_rom_15
  .prg_rom_16    : { *(.prg_rom_16    .prg_rom_16.*)    } >prg_rom_16
  .prg_rom_17    : { *(.prg_rom_17    .prg_rom_17.*)    } >prg_rom_17
  .prg_rom_18    : { *(.prg_rom_18    .prg_rom_18.*)    } >prg_rom_18
  .prg_rom_19    : { *(.prg_rom_19    .prg_rom_19.*)    } >prg_rom_19
  .prg_rom_20    : { *(.prg_rom_20    .prg_rom_20.*)    } >prg_rom_20
  .prg_rom_21    : { *(.prg_rom_21    .prg_rom_21.*)    } >prg_rom_21
  .prg_rom_22    : { *(.prg_rom_22    .prg_rom_22.*)    } >prg_rom_22
  .prg_rom_23    : { *(.prg_rom_23    .prg_rom_23.*)    } >prg_rom_23
  .prg_rom_24    : { *(.prg_rom_24    .prg_rom_24.*)    } >prg_rom_24
  .prg_rom_25    : { *(.prg_rom_25    .prg_rom_25.*)    } >prg_rom_25
  .prg_rom_26    : { *(.prg_rom_26    .prg_rom_26.*)    } >prg_rom_26
  .prg_rom_27    : { *(.prg_rom_27    .prg_rom_27.*)    } >prg_rom_27
  .prg_rom_28    : { *(.prg_rom_28    .prg_rom_28.*)    } >prg_rom_28
  .prg_rom_29    : { *(.prg_rom_29    .prg_rom_29.*)    } >prg_rom_29
  .prg_rom_30    : { *(.prg_rom_30    .prg_rom_30.*)    } >prg_rom_30
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed
}

INCLUDE dpcm.ld

SECTIONS {
  .reset       : { KEEP(*(.reset))       } >reset
  .reset_fixed : { KEEP(*(.reset_fixed)) } >reset_fixed
}

PROVIDE(__prg_rom_size = 512);

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)     FULL(reset, 0, LENGTH(prg_rom_0)  ? LENGTH(reset) : 0)
  FULL(prg_rom_1)     FULL(reset, 0, LENGTH(prg_rom_1)  ? LENGTH(reset) : 0)
  FULL(prg_rom_2)     FULL(reset, 0, LENGTH(prg_rom_2)  ? LENGTH(reset) : 0)
  FULL(prg_rom_3)     FULL(reset, 0, LENGTH(prg_rom_3)  ? LENGTH(reset) : 0)
  FULL(prg_rom_4)     FULL(reset, 0, LENGTH(prg_rom_4)  ? LENGTH(reset) : 0)
  FULL(prg_rom_5)     FULL(reset, 0, LENGTH(prg_rom_5)  ? LENGTH(reset) : 0)
  FULL(prg_rom_6)     FULL(reset, 0, LENGTH(prg_rom_6)  ? LENGTH(reset) : 0)
  FULL(prg_rom_7)     FULL(reset, 0, LENGTH(prg_rom_7)  ? LENGTH(reset) : 0)
  FULL(prg_rom_8)     FULL(reset, 0, LENGTH(prg_rom_8)  ? LENGTH(reset) : 0)
  FULL(prg_rom_9)     FULL(reset, 0, LENGTH(prg_rom_9)  ? LENGTH(reset) : 0)
  FULL(prg_rom_10)    FULL(reset, 0, LENGTH(prg_rom_10) ? LENGTH(reset) : 0)
  FULL(prg_rom_11)    FULL(reset, 0, LENGTH(prg_rom_11) ? LENGTH(reset) : 0)
  FULL(prg_rom_12)    FULL(reset, 0, LENGTH(prg_rom_12) ? LENGTH(reset) : 0)
  FULL(prg_rom_13)    FULL(reset, 0, LENGTH(prg_rom_13) ? LENGTH(reset) : 0)
  FULL(prg_rom_14)    FULL(reset, 0, LENGTH(prg_rom_14) ? LENGTH(reset) : 0)
  FULL(prg_rom_fixed) FULL(reset_fixed)

  FULL(prg_rom_16)    FULL(reset, 0, LENGTH(prg_rom_16) ? LENGTH(reset) : 0)
  FULL(prg_rom_17)    FULL(reset, 0, LENGTH(prg_rom_17) ? LENGTH(reset) : 0)
  FULL(prg_rom_18)    FULL(reset, 0, LENGTH(prg_rom_18) ? LENGTH(reset) : 0)
  FULL(prg_rom_19)    FULL(reset, 0, LENGTH(prg_rom_19) ? LENGTH(reset) : 0)
  FULL(prg_rom_20)    FULL(reset, 0, LENGTH(prg_rom_20) ? LENGTH(reset) : 0)
  FULL(prg_rom_21)    FULL(reset, 0, LENGTH(prg_rom_21) ? LENGTH(reset) : 0)
  FULL(prg_rom_22)    FULL(reset, 0, LENGTH(prg_rom_22) ? LENGTH(reset) : 0)
  FULL(prg_rom_23)    FULL(reset, 0, LENGTH(prg_rom_23) ? LENGTH(reset) : 0)
  FULL(prg_rom_24)    FULL(reset, 0, LENGTH(prg_rom_24) ? LENGTH(reset) : 0)
  FULL(prg_rom_25)    FULL(reset, 0, LENGTH(prg_rom_25) ? LENGTH(reset) : 0)
  FULL(prg_rom_26)    FULL(reset, 0, LENGTH(prg_rom_26) ? LENGTH(reset) : 0)
  FULL(prg_rom_27)    FULL(reset, 0, LENGTH(prg_rom_27) ? LENGTH(reset) : 0)
  FULL(prg_rom_28)    FULL(reset, 0, LENGTH(prg_rom_28) ? LENGTH(reset) : 0)
  FULL(prg_rom_29)    FULL(reset, 0, LENGTH(prg_rom_29) ? LENGTH(reset) : 0)
  FULL(prg_rom_30)    FULL(reset, 0, LENGTH(prg_rom_30) ? LENGTH(reset) : 0)
  FULL(prg_rom_fixed) FULL(reset_fixed)
  
  FULL(chr_rom)
}
