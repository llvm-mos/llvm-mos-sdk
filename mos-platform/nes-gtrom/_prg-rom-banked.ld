INPUT(reset.o)
__prg_rom_0_lma = 0x008000;
__prg_rom_1_lma = 0x018000;
__prg_rom_2_lma = 0x028000;
__prg_rom_3_lma = 0x038000;
__prg_rom_4_lma = 0x048000;
__prg_rom_5_lma = 0x058000;
__prg_rom_6_lma = 0x068000;
__prg_rom_7_lma = 0x078000;
__prg_rom_8_lma = 0x088000;
__prg_rom_9_lma = 0x098000;
__prg_rom_10_lma = 0x0a8000;
__prg_rom_11_lma = 0x0b8000;
__prg_rom_12_lma = 0x0c8000;
__prg_rom_13_lma = 0x0d8000;
__prg_rom_14_lma = 0x0e8000;
__prg_rom_15_lma = 0x0f8000;

__prg_rom_0_offset = 0x000000;
__prg_rom_1_offset = 0x008000;
__prg_rom_2_offset = 0x010000;
__prg_rom_3_offset = 0x018000;
__prg_rom_4_offset = 0x020000;
__prg_rom_5_offset = 0x028000;
__prg_rom_6_offset = 0x030000;
__prg_rom_7_offset = 0x038000;
__prg_rom_8_offset = 0x040000;
__prg_rom_9_offset = 0x048000;
__prg_rom_10_offset = 0x050000;
__prg_rom_11_offset = 0x058000;
__prg_rom_12_offset = 0x060000;
__prg_rom_13_offset = 0x068000;
__prg_rom_14_offset = 0x070000;
__prg_rom_15_offset = 0x078000;

MEMORY {
  /* PRG-ROM LMAs. */
  prg_rom_0 : ORIGIN = __prg_rom_0_lma, LENGTH = __prg_rom_size >= 32 ? 0x8000 - 0x6 : 0
  prg_rom_1 : ORIGIN = __prg_rom_1_lma, LENGTH = __prg_rom_size >= 64 ? 0x8000 - 0x6 : 0
  prg_rom_2 : ORIGIN = __prg_rom_2_lma, LENGTH = __prg_rom_size >= 128 ? 0x8000 - 0x6 : 0
  prg_rom_3 : ORIGIN = __prg_rom_3_lma, LENGTH = __prg_rom_size >= 128 ? 0x8000 - 0x6 : 0
  prg_rom_4 : ORIGIN = __prg_rom_4_lma, LENGTH = __prg_rom_size >= 256 ? 0x8000 - 0x6 : 0
  prg_rom_5 : ORIGIN = __prg_rom_5_lma, LENGTH = __prg_rom_size >= 256 ? 0x8000 - 0x6 : 0
  prg_rom_6 : ORIGIN = __prg_rom_6_lma, LENGTH = __prg_rom_size >= 256 ? 0x8000 - 0x6 : 0
  prg_rom_7 : ORIGIN = __prg_rom_7_lma, LENGTH = __prg_rom_size >= 256 ? 0x8000 - 0x6 : 0
  prg_rom_8 : ORIGIN = __prg_rom_8_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_9 : ORIGIN = __prg_rom_9_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_10 : ORIGIN = __prg_rom_10_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_11 : ORIGIN = __prg_rom_11_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_12 : ORIGIN = __prg_rom_12_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_13 : ORIGIN = __prg_rom_13_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_14 : ORIGIN = __prg_rom_14_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  prg_rom_15 : ORIGIN = __prg_rom_15_lma, LENGTH = __prg_rom_size >= 512 ? 0x8000 - 0x6 : 0
  vectors : ORIGIN = 0x10000 - 0x6, LENGTH = 0x6

  /* CHR-ROM LMAs. */
  chr_rom_0   : ORIGIN = 0x01000000, LENGTH = __chr_rom_size >= 8    ? 0x2000 : 0
  chr_rom_1   : ORIGIN = 0x01002000, LENGTH = __chr_rom_size >= 16   ? 0x2000 : 0
}

REGION_ALIAS("c_readonly", prg_rom_0)

SECTIONS {
  /* Define a fixed section at the beginning of PRG-ROM bank 0. */
  .prg_rom_fixed : {
    *(.prg_rom_fixed .prg_rom_fixed.*)
    __prg_rom_fixed_end = .;
    __prg_rom_fixed_size = __prg_rom_fixed_end - __prg_rom_0_lma;
  } >prg_rom_0

  /* Offset each non-fixed bank section's LMA by the fixed section. */
  /* This is accounted for in the custom output format. */
  .prg_rom_0 : {
      . = __prg_rom_0_lma + __prg_rom_fixed_size;
      *(.prg_rom_0 .prg_rom_0.*)
  } >prg_rom_0
  .prg_rom_1 : {
      . = __prg_rom_1_lma + __prg_rom_fixed_size;
      *(.prg_rom_1 .prg_rom_1.*)
  } >prg_rom_1
  .prg_rom_2 : {
      . = __prg_rom_2_lma + __prg_rom_fixed_size;
      *(.prg_rom_2 .prg_rom_2.*)
  } >prg_rom_2
  .prg_rom_3 : {
      . = __prg_rom_3_lma + __prg_rom_fixed_size;
      *(.prg_rom_3 .prg_rom_3.*)
  } >prg_rom_3
  .prg_rom_4 : {
      . = __prg_rom_4_lma + __prg_rom_fixed_size;
      *(.prg_rom_4 .prg_rom_4.*)
  } >prg_rom_4
  .prg_rom_5 : {
      . = __prg_rom_5_lma + __prg_rom_fixed_size;
      *(.prg_rom_5 .prg_rom_5.*)
  } >prg_rom_5
  .prg_rom_6 : {
      . = __prg_rom_6_lma + __prg_rom_fixed_size;
      *(.prg_rom_6 .prg_rom_6.*)
  } >prg_rom_6
  .prg_rom_7 : {
      . = __prg_rom_7_lma + __prg_rom_fixed_size;
      *(.prg_rom_7 .prg_rom_7.*)
  } >prg_rom_7
  .prg_rom_8 : {
      . = __prg_rom_8_lma + __prg_rom_fixed_size;
      *(.prg_rom_8 .prg_rom_8.*)
  } >prg_rom_8
  .prg_rom_9 : {
      . = __prg_rom_9_lma + __prg_rom_fixed_size;
      *(.prg_rom_9 .prg_rom_9.*)
  } >prg_rom_9
  .prg_rom_10 : {
      . = __prg_rom_10_lma + __prg_rom_fixed_size;
      *(.prg_rom_10 .prg_rom_10.*)
  } >prg_rom_10
  .prg_rom_11 : {
      . = __prg_rom_11_lma + __prg_rom_fixed_size;
      *(.prg_rom_11 .prg_rom_11.*)
  } >prg_rom_11
  .prg_rom_12 : {
      . = __prg_rom_12_lma + __prg_rom_fixed_size;
      *(.prg_rom_12 .prg_rom_12.*)
  } >prg_rom_12
  .prg_rom_13 : {
      . = __prg_rom_13_lma + __prg_rom_fixed_size;
      *(.prg_rom_13 .prg_rom_13.*)
  } >prg_rom_13
  .prg_rom_14 : {
      . = __prg_rom_14_lma + __prg_rom_fixed_size;
      *(.prg_rom_14 .prg_rom_14.*)
  } >prg_rom_14
  .prg_rom_15 : {
      . = __prg_rom_15_lma + __prg_rom_fixed_size;
      *(.prg_rom_15 .prg_rom_15.*)
  } >prg_rom_15

  .chr_rom_0   : { KEEP(*(.chr_rom_0   .chr_rom_0.*)) }   >chr_rom_0
  .chr_rom_1   : { KEEP(*(.chr_rom_1   .chr_rom_1.*)) }   >chr_rom_1
}

SECTIONS {
  .vectors : { KEEP(*(.vectors)) } >vectors
}
