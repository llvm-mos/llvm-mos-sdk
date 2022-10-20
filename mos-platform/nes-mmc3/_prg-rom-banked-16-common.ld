ASSERT(__prg_rom_size > 32,
       "For less than 32KiB of PRG-ROM, use fixed banking.");

MEMORY {
  prg_rom_0_vma     : ORIGIN = 0x000000 + __prg_rom_0,  LENGTH = 0x2000
  prg_rom_1_vma     : ORIGIN = 0x010000 + __prg_rom_1,  LENGTH = 0x2000
  prg_rom_2_vma     : ORIGIN = 0x020000 + __prg_rom_2,  LENGTH = 0x2000
  prg_rom_3_vma     : ORIGIN = 0x030000 + __prg_rom_3,  LENGTH = 0x2000
  prg_rom_4_vma     : ORIGIN = 0x040000 + __prg_rom_4,  LENGTH = 0x2000
  prg_rom_5_vma     : ORIGIN = 0x050000 + __prg_rom_5,  LENGTH = 0x2000
  prg_rom_6_vma     : ORIGIN = 0x060000 + __prg_rom_6,  LENGTH = 0x2000
  prg_rom_7_vma     : ORIGIN = 0x070000 + __prg_rom_7,  LENGTH = 0x2000
  prg_rom_8_vma     : ORIGIN = 0x080000 + __prg_rom_8,  LENGTH = 0x2000
  prg_rom_9_vma     : ORIGIN = 0x090000 + __prg_rom_9,  LENGTH = 0x2000
  prg_rom_10_vma    : ORIGIN = 0x0a0000 + __prg_rom_10, LENGTH = 0x2000
  prg_rom_11_vma    : ORIGIN = 0x0b0000 + __prg_rom_11, LENGTH = 0x2000
  prg_rom_12_vma    : ORIGIN = 0x0c0000 + __prg_rom_12, LENGTH = 0x2000
  prg_rom_13_vma    : ORIGIN = 0x0d0000 + __prg_rom_13, LENGTH = 0x2000
  prg_rom_14_vma    : ORIGIN = 0x0e0000 + __prg_rom_14, LENGTH = 0x2000
  prg_rom_15_vma    : ORIGIN = 0x0f0000 + __prg_rom_15, LENGTH = 0x2000
  prg_rom_16_vma    : ORIGIN = 0x100000 + __prg_rom_16, LENGTH = 0x2000
  prg_rom_17_vma    : ORIGIN = 0x110000 + __prg_rom_17, LENGTH = 0x2000
  prg_rom_18_vma    : ORIGIN = 0x120000 + __prg_rom_18, LENGTH = 0x2000
  prg_rom_19_vma    : ORIGIN = 0x130000 + __prg_rom_19, LENGTH = 0x2000
  prg_rom_20_vma    : ORIGIN = 0x140000 + __prg_rom_20, LENGTH = 0x2000
  prg_rom_21_vma    : ORIGIN = 0x150000 + __prg_rom_21, LENGTH = 0x2000
  prg_rom_22_vma    : ORIGIN = 0x160000 + __prg_rom_22, LENGTH = 0x2000
  prg_rom_23_vma    : ORIGIN = 0x170000 + __prg_rom_23, LENGTH = 0x2000
  prg_rom_24_vma    : ORIGIN = 0x180000 + __prg_rom_24, LENGTH = 0x2000
  prg_rom_25_vma    : ORIGIN = 0x190000 + __prg_rom_25, LENGTH = 0x2000
  prg_rom_26_vma    : ORIGIN = 0x1a0000 + __prg_rom_26, LENGTH = 0x2000
  prg_rom_27_vma    : ORIGIN = 0x1b0000 + __prg_rom_27, LENGTH = 0x2000
  prg_rom_28_vma    : ORIGIN = 0x1c0000 + __prg_rom_28, LENGTH = 0x2000
  prg_rom_29_vma    : ORIGIN = 0x1d0000 + __prg_rom_29, LENGTH = 0x2000
  prg_rom_30_vma    : ORIGIN = 0x1e0000 + __prg_rom_30, LENGTH = 0x2000
  prg_rom_31_vma    : ORIGIN = 0x1f0000 + __prg_rom_31, LENGTH = 0x2000
  prg_rom_32_vma    : ORIGIN = 0x200000 + __prg_rom_32, LENGTH = 0x2000
  prg_rom_33_vma    : ORIGIN = 0x210000 + __prg_rom_33, LENGTH = 0x2000
  prg_rom_34_vma    : ORIGIN = 0x220000 + __prg_rom_34, LENGTH = 0x2000
  prg_rom_35_vma    : ORIGIN = 0x230000 + __prg_rom_35, LENGTH = 0x2000
  prg_rom_36_vma    : ORIGIN = 0x240000 + __prg_rom_36, LENGTH = 0x2000
  prg_rom_37_vma    : ORIGIN = 0x250000 + __prg_rom_37, LENGTH = 0x2000
  prg_rom_38_vma    : ORIGIN = 0x260000 + __prg_rom_38, LENGTH = 0x2000
  prg_rom_39_vma    : ORIGIN = 0x270000 + __prg_rom_39, LENGTH = 0x2000
  prg_rom_40_vma    : ORIGIN = 0x280000 + __prg_rom_40, LENGTH = 0x2000
  prg_rom_41_vma    : ORIGIN = 0x290000 + __prg_rom_41, LENGTH = 0x2000
  prg_rom_42_vma    : ORIGIN = 0x2a0000 + __prg_rom_42, LENGTH = 0x2000
  prg_rom_43_vma    : ORIGIN = 0x2b0000 + __prg_rom_43, LENGTH = 0x2000
  prg_rom_44_vma    : ORIGIN = 0x2c0000 + __prg_rom_44, LENGTH = 0x2000
  prg_rom_45_vma    : ORIGIN = 0x2d0000 + __prg_rom_45, LENGTH = 0x2000
  prg_rom_46_vma    : ORIGIN = 0x2e0000 + __prg_rom_46, LENGTH = 0x2000
  prg_rom_47_vma    : ORIGIN = 0x2f0000 + __prg_rom_47, LENGTH = 0x2000
  prg_rom_48_vma    : ORIGIN = 0x300000 + __prg_rom_48, LENGTH = 0x2000
  prg_rom_49_vma    : ORIGIN = 0x310000 + __prg_rom_49, LENGTH = 0x2000
  prg_rom_50_vma    : ORIGIN = 0x320000 + __prg_rom_50, LENGTH = 0x2000
  prg_rom_51_vma    : ORIGIN = 0x330000 + __prg_rom_51, LENGTH = 0x2000
  prg_rom_52_vma    : ORIGIN = 0x340000 + __prg_rom_52, LENGTH = 0x2000
  prg_rom_53_vma    : ORIGIN = 0x350000 + __prg_rom_53, LENGTH = 0x2000
  prg_rom_54_vma    : ORIGIN = 0x360000 + __prg_rom_54, LENGTH = 0x2000
  prg_rom_55_vma    : ORIGIN = 0x370000 + __prg_rom_55, LENGTH = 0x2000
  prg_rom_56_vma    : ORIGIN = 0x380000 + __prg_rom_56, LENGTH = 0x2000
  prg_rom_57_vma    : ORIGIN = 0x390000 + __prg_rom_57, LENGTH = 0x2000
  prg_rom_58_vma    : ORIGIN = 0x3a0000 + __prg_rom_58, LENGTH = 0x2000
  prg_rom_59_vma    : ORIGIN = 0x3b0000 + __prg_rom_59, LENGTH = 0x2000
  prg_rom_60_vma    : ORIGIN = 0x3c0000 + __prg_rom_60, LENGTH = 0x2000
  prg_rom_61_vma    : ORIGIN = 0x3d0000 + __prg_rom_61, LENGTH = 0x2000
}

INCLUDE dpcm.ld
INCLUDE reset.ld
