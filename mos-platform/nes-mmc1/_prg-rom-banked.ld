INPUT(reset.o)

MEMORY {
  /* PRG-ROM LMAs. */
  prg_rom_0_lma     : ORIGIN = 0x01000000, LENGTH = __prg_rom_size >= 32  ? 0x4000 - 12 : 0
  prg_rom_1_lma     : ORIGIN = 0x01004000, LENGTH = __prg_rom_size >= 32  ? 0x4000 - 12 : 0
  prg_rom_2_lma     : ORIGIN = 0x01008000, LENGTH = __prg_rom_size >= 64  ? 0x4000 - 12 : 0
  prg_rom_3_lma     : ORIGIN = 0x0100c000, LENGTH = __prg_rom_size >  64  ? 0x4000 - 12 : 0
  prg_rom_4_lma     : ORIGIN = 0x01010000, LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_5_lma     : ORIGIN = 0x01014000, LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_6_lma     : ORIGIN = 0x01018000, LENGTH = __prg_rom_size >= 128 ? 0x4000 - 12 : 0
  prg_rom_7_lma     : ORIGIN = 0x0101c000, LENGTH = __prg_rom_size >  128 ? 0x4000 - 12 : 0
  prg_rom_8_lma     : ORIGIN = 0x01020000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_9_lma     : ORIGIN = 0x01024000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_10_lma    : ORIGIN = 0x01028000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_11_lma    : ORIGIN = 0x0102c000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_12_lma    : ORIGIN = 0x01030000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_13_lma    : ORIGIN = 0x01034000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_14_lma    : ORIGIN = 0x01038000, LENGTH = __prg_rom_size >= 256 ? 0x4000 - 12 : 0
  prg_rom_fixed_lma : ORIGIN = 0x01000000 + __prg_rom_size * 1024 - 0x4000, LENGTH = 0x4000 - 12

  /* PRG-ROM VMAs. */
  prg_rom_0_vma     : ORIGIN = 0x008000, LENGTH = 0x4000 - 12
  prg_rom_1_vma     : ORIGIN = 0x018000, LENGTH = 0x4000 - 12
  prg_rom_2_vma     : ORIGIN = 0x028000, LENGTH = 0x4000 - 12
  prg_rom_3_vma     : ORIGIN = 0x038000, LENGTH = 0x4000 - 12
  prg_rom_4_vma     : ORIGIN = 0x048000, LENGTH = 0x4000 - 12
  prg_rom_5_vma     : ORIGIN = 0x058000, LENGTH = 0x4000 - 12
  prg_rom_6_vma     : ORIGIN = 0x068000, LENGTH = 0x4000 - 12
  prg_rom_7_vma     : ORIGIN = 0x078000, LENGTH = 0x4000 - 12
  prg_rom_8_vma     : ORIGIN = 0x088000, LENGTH = 0x4000 - 12
  prg_rom_9_vma     : ORIGIN = 0x098000, LENGTH = 0x4000 - 12
  prg_rom_10_vma    : ORIGIN = 0x0a8000, LENGTH = 0x4000 - 12
  prg_rom_11_vma    : ORIGIN = 0x0b8000, LENGTH = 0x4000 - 12
  prg_rom_12_vma    : ORIGIN = 0x0c8000, LENGTH = 0x4000 - 12
  prg_rom_13_vma    : ORIGIN = 0x0d8000, LENGTH = 0x4000 - 12
  prg_rom_14_vma    : ORIGIN = 0x0e8000, LENGTH = 0x4000 - 12
  prg_rom_fixed_vma : ORIGIN = 0xc000,   LENGTH = 0x4000 - 12

  /* Reset stub addresses. */
  reset_0  : ORIGIN = ORIGIN(prg_rom_0_lma)  + LENGTH(prg_rom_0_lma),  LENGTH = 12
  reset_1  : ORIGIN = ORIGIN(prg_rom_1_lma)  + LENGTH(prg_rom_1_lma),  LENGTH = 12
  reset_2  : ORIGIN = ORIGIN(prg_rom_2_lma)  + LENGTH(prg_rom_2_lma),  LENGTH = 12
  reset_3  : ORIGIN = ORIGIN(prg_rom_3_lma)  + LENGTH(prg_rom_3_lma),  LENGTH = 12
  reset_4  : ORIGIN = ORIGIN(prg_rom_4_lma)  + LENGTH(prg_rom_4_lma),  LENGTH = 12
  reset_5  : ORIGIN = ORIGIN(prg_rom_5_lma)  + LENGTH(prg_rom_5_lma),  LENGTH = 12
  reset_6  : ORIGIN = ORIGIN(prg_rom_6_lma)  + LENGTH(prg_rom_6_lma),  LENGTH = 12
  reset_7  : ORIGIN = ORIGIN(prg_rom_7_lma)  + LENGTH(prg_rom_7_lma),  LENGTH = 12
  reset_8  : ORIGIN = ORIGIN(prg_rom_8_lma)  + LENGTH(prg_rom_8_lma),  LENGTH = 12
  reset_9  : ORIGIN = ORIGIN(prg_rom_9_lma)  + LENGTH(prg_rom_9_lma),  LENGTH = 12
  reset_10 : ORIGIN = ORIGIN(prg_rom_10_lma) + LENGTH(prg_rom_10_lma), LENGTH = 12
  reset_11 : ORIGIN = ORIGIN(prg_rom_11_lma) + LENGTH(prg_rom_11_lma), LENGTH = 12
  reset_12 : ORIGIN = ORIGIN(prg_rom_12_lma) + LENGTH(prg_rom_12_lma), LENGTH = 12
  reset_13 : ORIGIN = ORIGIN(prg_rom_13_lma) + LENGTH(prg_rom_13_lma), LENGTH = 12
  reset_14 : ORIGIN = ORIGIN(prg_rom_14_lma) + LENGTH(prg_rom_14_lma), LENGTH = 12

  reset_fixed : ORIGIN = ORIGIN(prg_rom_fixed_lma) + LENGTH(prg_rom_fixed_lma), LENGTH = 12
}

REGION_ALIAS("c_rom_vma", prg_rom_fixed_vma)
REGION_ALIAS("c_rom_lma", prg_rom_fixed_lma)

SECTIONS {
  .prg_rom_0     : { *(.prg_rom_0     .prg_rom_0.*)     } >prg_rom_0_vma     AT>prg_rom_0_lma
  .prg_rom_1     : { *(.prg_rom_1     .prg_rom_1.*)     } >prg_rom_1_vma     AT>prg_rom_1_lma
  .prg_rom_2     : { *(.prg_rom_2     .prg_rom_2.*)     } >prg_rom_2_vma     AT>prg_rom_2_lma
  .prg_rom_3     : { *(.prg_rom_3     .prg_rom_3.*)     } >prg_rom_3_vma     AT>prg_rom_3_lma
  .prg_rom_4     : { *(.prg_rom_4     .prg_rom_4.*)     } >prg_rom_4_vma     AT>prg_rom_4_lma
  .prg_rom_5     : { *(.prg_rom_5     .prg_rom_5.*)     } >prg_rom_5_vma     AT>prg_rom_5_lma
  .prg_rom_6     : { *(.prg_rom_6     .prg_rom_6.*)     } >prg_rom_6_vma     AT>prg_rom_6_lma
  .prg_rom_7     : { *(.prg_rom_7     .prg_rom_7.*)     } >prg_rom_7_vma     AT>prg_rom_7_lma
  .prg_rom_8     : { *(.prg_rom_8     .prg_rom_8.*)     } >prg_rom_8_vma     AT>prg_rom_8_lma
  .prg_rom_9     : { *(.prg_rom_9     .prg_rom_9.*)     } >prg_rom_9_vma     AT>prg_rom_9_lma
  .prg_rom_10    : { *(.prg_rom_10    .prg_rom_10.*)    } >prg_rom_10_vma    AT>prg_rom_10_lma
  .prg_rom_11    : { *(.prg_rom_11    .prg_rom_11.*)    } >prg_rom_11_vma    AT>prg_rom_11_lma
  .prg_rom_12    : { *(.prg_rom_12    .prg_rom_12.*)    } >prg_rom_12_vma    AT>prg_rom_12_lma
  .prg_rom_13    : { *(.prg_rom_13    .prg_rom_13.*)    } >prg_rom_13_vma    AT>prg_rom_13_lma
  .prg_rom_14    : { *(.prg_rom_14    .prg_rom_14.*)    } >prg_rom_14_vma    AT>prg_rom_14_lma
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed_vma AT>prg_rom_fixed_lma

  .reset_fixed : { KEEP(*(.reset_last)) } >reset_fixed
}
