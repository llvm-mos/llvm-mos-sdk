
PROVIDE(__prg_rom_size = 512);

ASSERT(__prg_rom_size > 32,
       "For less than 32KiB of PRG-ROM, use fixed banking.");

__prg_rom_0_lma  = 0x000000 + __prg_rom_0;
__prg_rom_1_lma  = 0x010000 + __prg_rom_1;
__prg_rom_2_lma  = 0x020000 + __prg_rom_2;
__prg_rom_3_lma  = 0x030000 + __prg_rom_3;
__prg_rom_4_lma  = 0x040000 + __prg_rom_4;
__prg_rom_5_lma  = 0x050000 + __prg_rom_5;
__prg_rom_6_lma  = 0x060000 + __prg_rom_6;
__prg_rom_7_lma  = 0x070000 + __prg_rom_7;
__prg_rom_8_lma  = 0x080000 + __prg_rom_8;
__prg_rom_9_lma  = 0x090000 + __prg_rom_9;
__prg_rom_10_lma = 0x0a0000 + __prg_rom_10;
__prg_rom_11_lma = 0x0b0000 + __prg_rom_11;
__prg_rom_12_lma = 0x0c0000 + __prg_rom_12;
__prg_rom_13_lma = 0x0d0000 + __prg_rom_13;
__prg_rom_14_lma = 0x0e0000 + __prg_rom_14;
__prg_rom_15_lma = 0x0f0000 + __prg_rom_15;
__prg_rom_16_lma = 0x100000 + __prg_rom_16;
__prg_rom_17_lma = 0x110000 + __prg_rom_17;
__prg_rom_18_lma = 0x120000 + __prg_rom_18;
__prg_rom_19_lma = 0x130000 + __prg_rom_19;
__prg_rom_20_lma = 0x140000 + __prg_rom_20;
__prg_rom_21_lma = 0x150000 + __prg_rom_21;
__prg_rom_22_lma = 0x160000 + __prg_rom_22;
__prg_rom_23_lma = 0x170000 + __prg_rom_23;
__prg_rom_24_lma = 0x180000 + __prg_rom_24;
__prg_rom_25_lma = 0x190000 + __prg_rom_25;
__prg_rom_26_lma = 0x1a0000 + __prg_rom_26;
__prg_rom_27_lma = 0x1b0000 + __prg_rom_27;
__prg_rom_28_lma = 0x1c0000 + __prg_rom_28;
__prg_rom_29_lma = 0x1d0000 + __prg_rom_29;
__prg_rom_30_lma = 0x1e0000 + __prg_rom_30;
__prg_rom_31_lma = 0x1f0000 + __prg_rom_31;
__prg_rom_32_lma = 0x200000 + __prg_rom_32;
__prg_rom_33_lma = 0x210000 + __prg_rom_33;
__prg_rom_34_lma = 0x220000 + __prg_rom_34;
__prg_rom_35_lma = 0x230000 + __prg_rom_35;
__prg_rom_36_lma = 0x240000 + __prg_rom_36;
__prg_rom_37_lma = 0x250000 + __prg_rom_37;
__prg_rom_38_lma = 0x260000 + __prg_rom_38;
__prg_rom_39_lma = 0x270000 + __prg_rom_39;
__prg_rom_40_lma = 0x280000 + __prg_rom_40;
__prg_rom_41_lma = 0x290000 + __prg_rom_41;
__prg_rom_42_lma = 0x2a0000 + __prg_rom_42;
__prg_rom_43_lma = 0x2b0000 + __prg_rom_43;
__prg_rom_44_lma = 0x2c0000 + __prg_rom_44;
__prg_rom_45_lma = 0x2d0000 + __prg_rom_45;
__prg_rom_46_lma = 0x2e0000 + __prg_rom_46;
__prg_rom_47_lma = 0x2f0000 + __prg_rom_47;
__prg_rom_48_lma = 0x300000 + __prg_rom_48;
__prg_rom_49_lma = 0x310000 + __prg_rom_49;
__prg_rom_50_lma = 0x320000 + __prg_rom_50;
__prg_rom_51_lma = 0x330000 + __prg_rom_51;
__prg_rom_52_lma = 0x340000 + __prg_rom_52;
__prg_rom_53_lma = 0x350000 + __prg_rom_53;
__prg_rom_54_lma = 0x360000 + __prg_rom_54;
__prg_rom_55_lma = 0x370000 + __prg_rom_55;
__prg_rom_56_lma = 0x380000 + __prg_rom_56;
__prg_rom_57_lma = 0x390000 + __prg_rom_57;
__prg_rom_58_lma = 0x3a0000 + __prg_rom_58;
__prg_rom_59_lma = 0x3b0000 + __prg_rom_59;
__prg_rom_60_lma = 0x3c0000 + __prg_rom_60;

__prg_rom_0_offset  = 0x00000;
__prg_rom_1_offset  = 0x02000;
__prg_rom_2_offset  = 0x04000;
__prg_rom_3_offset  = 0x06000;
__prg_rom_4_offset  = 0x08000;
__prg_rom_5_offset  = 0x0a000;
__prg_rom_6_offset  = 0x0c000;
__prg_rom_7_offset  = 0x0e000;
__prg_rom_8_offset  = 0x10000;
__prg_rom_9_offset  = 0x12000;
__prg_rom_10_offset = 0x14000;
__prg_rom_11_offset = 0x16000;
__prg_rom_12_offset = 0x18000;
__prg_rom_13_offset = 0x1a000;
__prg_rom_14_offset = 0x1c000;
__prg_rom_15_offset = 0x1e000;
__prg_rom_16_offset = 0x20000;
__prg_rom_17_offset = 0x22000;
__prg_rom_18_offset = 0x24000;
__prg_rom_19_offset = 0x26000;
__prg_rom_20_offset = 0x28000;
__prg_rom_21_offset = 0x2a000;
__prg_rom_22_offset = 0x2c000;
__prg_rom_23_offset = 0x2e000;
__prg_rom_24_offset = 0x30000;
__prg_rom_25_offset = 0x32000;
__prg_rom_26_offset = 0x34000;
__prg_rom_27_offset = 0x36000;
__prg_rom_28_offset = 0x38000;
__prg_rom_29_offset = 0x3a000;
__prg_rom_30_offset = 0x3c000;
__prg_rom_31_offset = 0x3e000;
__prg_rom_32_offset = 0x40000;
__prg_rom_33_offset = 0x42000;
__prg_rom_34_offset = 0x44000;
__prg_rom_35_offset = 0x46000;
__prg_rom_36_offset = 0x48000;
__prg_rom_37_offset = 0x4a000;
__prg_rom_38_offset = 0x4c000;
__prg_rom_39_offset = 0x4e000;
__prg_rom_40_offset = 0x50000;
__prg_rom_41_offset = 0x52000;
__prg_rom_42_offset = 0x54000;
__prg_rom_43_offset = 0x56000;
__prg_rom_44_offset = 0x58000;
__prg_rom_45_offset = 0x5a000;
__prg_rom_46_offset = 0x5c000;
__prg_rom_47_offset = 0x5e000;
__prg_rom_48_offset = 0x60000;
__prg_rom_49_offset = 0x62000;
__prg_rom_50_offset = 0x64000;
__prg_rom_51_offset = 0x66000;
__prg_rom_52_offset = 0x68000;
__prg_rom_53_offset = 0x6a000;
__prg_rom_54_offset = 0x6c000;
__prg_rom_55_offset = 0x6e000;
__prg_rom_56_offset = 0x70000;
__prg_rom_57_offset = 0x72000;
__prg_rom_58_offset = 0x74000;
__prg_rom_59_offset = 0x76000;
__prg_rom_60_offset = 0x78000;

MEMORY {
  prg_rom_0     : ORIGIN = __prg_rom_0_lma,  LENGTH = 0x2000
  prg_rom_1     : ORIGIN = __prg_rom_1_lma,  LENGTH = 0x2000
  prg_rom_2     : ORIGIN = __prg_rom_2_lma,  LENGTH = 0x2000
  prg_rom_3     : ORIGIN = __prg_rom_3_lma,  LENGTH = 0x2000
  prg_rom_4     : ORIGIN = __prg_rom_4_lma,  LENGTH = 0x2000
  prg_rom_5     : ORIGIN = __prg_rom_5_lma,  LENGTH = 0x2000
  prg_rom_6     : ORIGIN = __prg_rom_6_lma,  LENGTH = __prg_rom_size >  64  ? 0x2000 : 0
  prg_rom_7     : ORIGIN = __prg_rom_7_lma,  LENGTH = __prg_rom_size >  64  ? 0x2000 : 0
  prg_rom_8     : ORIGIN = __prg_rom_8_lma,  LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_9     : ORIGIN = __prg_rom_9_lma,  LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_10    : ORIGIN = __prg_rom_10_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_11    : ORIGIN = __prg_rom_11_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_12    : ORIGIN = __prg_rom_12_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_13    : ORIGIN = __prg_rom_13_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_14    : ORIGIN = __prg_rom_14_lma, LENGTH = __prg_rom_size >  128 ? 0x2000 : 0
  prg_rom_15    : ORIGIN = __prg_rom_15_lma, LENGTH = __prg_rom_size >  128 ? 0x2000 : 0
  prg_rom_16    : ORIGIN = __prg_rom_16_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_17    : ORIGIN = __prg_rom_17_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_18    : ORIGIN = __prg_rom_18_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_19    : ORIGIN = __prg_rom_19_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_20    : ORIGIN = __prg_rom_20_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_21    : ORIGIN = __prg_rom_21_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_22    : ORIGIN = __prg_rom_22_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_23    : ORIGIN = __prg_rom_23_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_24    : ORIGIN = __prg_rom_24_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_25    : ORIGIN = __prg_rom_25_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_26    : ORIGIN = __prg_rom_26_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_27    : ORIGIN = __prg_rom_27_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_28    : ORIGIN = __prg_rom_28_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_29    : ORIGIN = __prg_rom_29_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_30    : ORIGIN = __prg_rom_30_lma, LENGTH = __prg_rom_size >  256 ? 0x2000 : 0
  prg_rom_31    : ORIGIN = __prg_rom_31_lma, LENGTH = __prg_rom_size >  256 ? 0x2000 : 0
  prg_rom_32    : ORIGIN = __prg_rom_32_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_33    : ORIGIN = __prg_rom_33_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_34    : ORIGIN = __prg_rom_34_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_35    : ORIGIN = __prg_rom_35_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_36    : ORIGIN = __prg_rom_36_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_37    : ORIGIN = __prg_rom_37_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_38    : ORIGIN = __prg_rom_38_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_39    : ORIGIN = __prg_rom_39_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_40    : ORIGIN = __prg_rom_40_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_41    : ORIGIN = __prg_rom_41_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_42    : ORIGIN = __prg_rom_42_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_43    : ORIGIN = __prg_rom_43_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_44    : ORIGIN = __prg_rom_44_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_45    : ORIGIN = __prg_rom_45_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_46    : ORIGIN = __prg_rom_46_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_47    : ORIGIN = __prg_rom_47_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_48    : ORIGIN = __prg_rom_48_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_49    : ORIGIN = __prg_rom_49_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_50    : ORIGIN = __prg_rom_50_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_51    : ORIGIN = __prg_rom_51_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_52    : ORIGIN = __prg_rom_52_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_53    : ORIGIN = __prg_rom_53_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_54    : ORIGIN = __prg_rom_54_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_55    : ORIGIN = __prg_rom_55_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_56    : ORIGIN = __prg_rom_56_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_57    : ORIGIN = __prg_rom_57_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_58    : ORIGIN = __prg_rom_58_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_59    : ORIGIN = __prg_rom_59_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_60    : ORIGIN = __prg_rom_60_lma, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
}

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
  .prg_rom_31    : { *(.prg_rom_31    .prg_rom_31.*)    } >prg_rom_31
  .prg_rom_32    : { *(.prg_rom_32    .prg_rom_32.*)    } >prg_rom_32
  .prg_rom_33    : { *(.prg_rom_33    .prg_rom_33.*)    } >prg_rom_33
  .prg_rom_34    : { *(.prg_rom_34    .prg_rom_34.*)    } >prg_rom_34
  .prg_rom_35    : { *(.prg_rom_35    .prg_rom_35.*)    } >prg_rom_35
  .prg_rom_36    : { *(.prg_rom_36    .prg_rom_36.*)    } >prg_rom_36
  .prg_rom_37    : { *(.prg_rom_37    .prg_rom_37.*)    } >prg_rom_37
  .prg_rom_38    : { *(.prg_rom_38    .prg_rom_38.*)    } >prg_rom_38
  .prg_rom_39    : { *(.prg_rom_39    .prg_rom_39.*)    } >prg_rom_39
  .prg_rom_40    : { *(.prg_rom_40    .prg_rom_40.*)    } >prg_rom_40
  .prg_rom_41    : { *(.prg_rom_41    .prg_rom_41.*)    } >prg_rom_41
  .prg_rom_42    : { *(.prg_rom_42    .prg_rom_42.*)    } >prg_rom_42
  .prg_rom_43    : { *(.prg_rom_43    .prg_rom_43.*)    } >prg_rom_43
  .prg_rom_44    : { *(.prg_rom_44    .prg_rom_44.*)    } >prg_rom_44
  .prg_rom_45    : { *(.prg_rom_45    .prg_rom_45.*)    } >prg_rom_45
  .prg_rom_46    : { *(.prg_rom_46    .prg_rom_46.*)    } >prg_rom_46
  .prg_rom_47    : { *(.prg_rom_47    .prg_rom_47.*)    } >prg_rom_47
  .prg_rom_48    : { *(.prg_rom_48    .prg_rom_48.*)    } >prg_rom_48
  .prg_rom_49    : { *(.prg_rom_49    .prg_rom_49.*)    } >prg_rom_49
  .prg_rom_50    : { *(.prg_rom_50    .prg_rom_50.*)    } >prg_rom_50
  .prg_rom_51    : { *(.prg_rom_51    .prg_rom_51.*)    } >prg_rom_51
  .prg_rom_52    : { *(.prg_rom_52    .prg_rom_52.*)    } >prg_rom_52
  .prg_rom_53    : { *(.prg_rom_53    .prg_rom_53.*)    } >prg_rom_53
  .prg_rom_54    : { *(.prg_rom_54    .prg_rom_54.*)    } >prg_rom_54
  .prg_rom_55    : { *(.prg_rom_55    .prg_rom_55.*)    } >prg_rom_55
  .prg_rom_56    : { *(.prg_rom_56    .prg_rom_56.*)    } >prg_rom_56
  .prg_rom_57    : { *(.prg_rom_57    .prg_rom_57.*)    } >prg_rom_57
  .prg_rom_58    : { *(.prg_rom_58    .prg_rom_58.*)    } >prg_rom_58
  .prg_rom_59    : { *(.prg_rom_59    .prg_rom_59.*)    } >prg_rom_59
  .prg_rom_60    : { *(.prg_rom_60    .prg_rom_60.*)    } >prg_rom_60
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed
}
