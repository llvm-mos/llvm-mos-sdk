/* NES-MMC3 iNES file linker script. */

INCLUDE nes.ld

ASSERT(__prg_ram_size + __prg_nvram_size <= 8,
       "MMC3 only supports up to 8KiB of PRG-(NV)RAM.")
ASSERT(__prg_rom_size <= 512, "MMC3 only supports up to 512KiB of PRG-ROM.")

MEMORY {
  prg_ram_vma : ORIGIN = 0x006000, LENGTH = 0x2000
  prg_ram_lma : ORIGIN = 0x03000000, LENGTH = (__prg_ram_size + __prg_nvram_size) * 1024

  prg_rom_0_lma  : ORIGIN = 0x01000000, LENGTH = MIN(__prg_rom_size * 1024, 0x2000)
  prg_rom_1_lma  : ORIGIN = 0x01002000, LENGTH = __prg_rom_size >= 16  ? 0x2000 : 0
  prg_rom_2_lma  : ORIGIN = 0x01004000, LENGTH = __prg_rom_size >  32  ? 0x2000 : 0
  prg_rom_3_lma  : ORIGIN = 0x01006000, LENGTH = __prg_rom_size >  32  ? 0x2000 : 0
  prg_rom_4_lma  : ORIGIN = 0x01008000, LENGTH = __prg_rom_size >= 64  ? 0x2000 : 0
  prg_rom_5_lma  : ORIGIN = 0x0100a000, LENGTH = __prg_rom_size >= 64  ? 0x2000 : 0
  prg_rom_6_lma  : ORIGIN = 0x0100c000, LENGTH = __prg_rom_size >  64  ? 0x2000 : 0
  prg_rom_7_lma  : ORIGIN = 0x0100e000, LENGTH = __prg_rom_size >  64  ? 0x2000 : 0
  prg_rom_8_lma  : ORIGIN = 0x01010000, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_9_lma  : ORIGIN = 0x01012000, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_10_lma : ORIGIN = 0x01014000, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_11_lma : ORIGIN = 0x01016000, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_12_lma : ORIGIN = 0x01018000, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_13_lma : ORIGIN = 0x0101a000, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_14_lma : ORIGIN = 0x0101c000, LENGTH = __prg_rom_size >  128 ? 0x2000 : 0
  prg_rom_15_lma : ORIGIN = 0x0101e000, LENGTH = __prg_rom_size >  128 ? 0x2000 : 0
  prg_rom_16_lma : ORIGIN = 0x01020000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_17_lma : ORIGIN = 0x01022000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_18_lma : ORIGIN = 0x01024000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_19_lma : ORIGIN = 0x01026000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_20_lma : ORIGIN = 0x01028000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_21_lma : ORIGIN = 0x0102a000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_22_lma : ORIGIN = 0x0102c000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_23_lma : ORIGIN = 0x0102e000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_24_lma : ORIGIN = 0x01030000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_25_lma : ORIGIN = 0x01032000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_26_lma : ORIGIN = 0x01034000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_27_lma : ORIGIN = 0x01036000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_28_lma : ORIGIN = 0x01038000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_29_lma : ORIGIN = 0x0103a000, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_30_lma : ORIGIN = 0x0103c000, LENGTH = __prg_rom_size >  256 ? 0x2000 : 0
  prg_rom_31_lma : ORIGIN = 0x0103e000, LENGTH = __prg_rom_size >  256 ? 0x2000 : 0
  prg_rom_32_lma : ORIGIN = 0x01040000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_33_lma : ORIGIN = 0x01042000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_34_lma : ORIGIN = 0x01044000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_35_lma : ORIGIN = 0x01046000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_36_lma : ORIGIN = 0x01048000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_37_lma : ORIGIN = 0x0104a000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_38_lma : ORIGIN = 0x0104c000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_39_lma : ORIGIN = 0x0104e000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_40_lma : ORIGIN = 0x01050000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_41_lma : ORIGIN = 0x01052000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_42_lma : ORIGIN = 0x01054000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_43_lma : ORIGIN = 0x01056000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_44_lma : ORIGIN = 0x01058000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_45_lma : ORIGIN = 0x0105a000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_46_lma : ORIGIN = 0x0105c000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_47_lma : ORIGIN = 0x0105e000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_48_lma : ORIGIN = 0x01060000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_49_lma : ORIGIN = 0x01062000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_50_lma : ORIGIN = 0x01064000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_51_lma : ORIGIN = 0x01066000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_52_lma : ORIGIN = 0x01068000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_53_lma : ORIGIN = 0x0106a000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_54_lma : ORIGIN = 0x0106c000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_55_lma : ORIGIN = 0x0106e000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_56_lma : ORIGIN = 0x01070000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_57_lma : ORIGIN = 0x01072000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_58_lma : ORIGIN = 0x01074000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_59_lma : ORIGIN = 0x01076000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_60_lma : ORIGIN = 0x01078000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_61_lma : ORIGIN = 0x0107a000, LENGTH = __prg_rom_size == 512 ? 0x2000 : 0

  chr_rom_0   : ORIGIN = 0x02000000, LENGTH = __chr_rom_size >= 1   ? 0x400 : 0
  chr_rom_1   : ORIGIN = 0x02000400, LENGTH = __chr_rom_size >= 2   ? 0x400 : 0
  chr_rom_2   : ORIGIN = 0x02000800, LENGTH = __chr_rom_size >= 4   ? 0x400 : 0
  chr_rom_3   : ORIGIN = 0x02000c00, LENGTH = __chr_rom_size >= 4   ? 0x400 : 0
  chr_rom_4   : ORIGIN = 0x02001000, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_5   : ORIGIN = 0x02001400, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_6   : ORIGIN = 0x02001800, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_7   : ORIGIN = 0x02001c00, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_8   : ORIGIN = 0x02002000, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_9   : ORIGIN = 0x02002400, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_10  : ORIGIN = 0x02002800, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_11  : ORIGIN = 0x02002c00, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_12  : ORIGIN = 0x02003000, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_13  : ORIGIN = 0x02003400, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_14  : ORIGIN = 0x02003800, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_15  : ORIGIN = 0x02003c00, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_16  : ORIGIN = 0x02004000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_17  : ORIGIN = 0x02004400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_18  : ORIGIN = 0x02004800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_19  : ORIGIN = 0x02004c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_20  : ORIGIN = 0x02005000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_21  : ORIGIN = 0x02005400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_22  : ORIGIN = 0x02005800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_23  : ORIGIN = 0x02005c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_24  : ORIGIN = 0x02006000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_25  : ORIGIN = 0x02006400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_26  : ORIGIN = 0x02006800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_27  : ORIGIN = 0x02006c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_28  : ORIGIN = 0x02007000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_29  : ORIGIN = 0x02007400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_30  : ORIGIN = 0x02007800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_31  : ORIGIN = 0x02007c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_32  : ORIGIN = 0x02008000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_33  : ORIGIN = 0x02008400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_34  : ORIGIN = 0x02008800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_35  : ORIGIN = 0x02008c00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_36  : ORIGIN = 0x02009000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_37  : ORIGIN = 0x02009400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_38  : ORIGIN = 0x02009800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_39  : ORIGIN = 0x02009c00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_40  : ORIGIN = 0x0200a000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_41  : ORIGIN = 0x0200a400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_42  : ORIGIN = 0x0200a800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_43  : ORIGIN = 0x0200ac00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_44  : ORIGIN = 0x0200b000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_45  : ORIGIN = 0x0200b400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_46  : ORIGIN = 0x0200b800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_47  : ORIGIN = 0x0200bc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_48  : ORIGIN = 0x0200c000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_49  : ORIGIN = 0x0200c400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_50  : ORIGIN = 0x0200c800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_51  : ORIGIN = 0x0200cc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_52  : ORIGIN = 0x0200d000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_53  : ORIGIN = 0x0200d400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_54  : ORIGIN = 0x0200d800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_55  : ORIGIN = 0x0200dc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_56  : ORIGIN = 0x0200e000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_57  : ORIGIN = 0x0200e400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_58  : ORIGIN = 0x0200e800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_59  : ORIGIN = 0x0200ec00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_60  : ORIGIN = 0x0200f000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_61  : ORIGIN = 0x0200f400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_62  : ORIGIN = 0x0200f800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_63  : ORIGIN = 0x0200fc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_64  : ORIGIN = 0x02010000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_65  : ORIGIN = 0x02010400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_66  : ORIGIN = 0x02010800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_67  : ORIGIN = 0x02010c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_68  : ORIGIN = 0x02011000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_69  : ORIGIN = 0x02011400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_70  : ORIGIN = 0x02011800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_71  : ORIGIN = 0x02011c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_72  : ORIGIN = 0x02012000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_73  : ORIGIN = 0x02012400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_74  : ORIGIN = 0x02012800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_75  : ORIGIN = 0x02012c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_76  : ORIGIN = 0x02013000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_77  : ORIGIN = 0x02013400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_78  : ORIGIN = 0x02013800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_79  : ORIGIN = 0x02013c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_80  : ORIGIN = 0x02014000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_81  : ORIGIN = 0x02014400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_82  : ORIGIN = 0x02014800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_83  : ORIGIN = 0x02014c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_84  : ORIGIN = 0x02015000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_85  : ORIGIN = 0x02015400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_86  : ORIGIN = 0x02015800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_87  : ORIGIN = 0x02015c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_88  : ORIGIN = 0x02016000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_89  : ORIGIN = 0x02016400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_90  : ORIGIN = 0x02016800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_91  : ORIGIN = 0x02016c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_92  : ORIGIN = 0x02017000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_93  : ORIGIN = 0x02017400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_94  : ORIGIN = 0x02017800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_95  : ORIGIN = 0x02017c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_96  : ORIGIN = 0x02018000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_97  : ORIGIN = 0x02018400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_98  : ORIGIN = 0x02018800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_99  : ORIGIN = 0x02018c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_100 : ORIGIN = 0x02019000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_101 : ORIGIN = 0x02019400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_102 : ORIGIN = 0x02019800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_103 : ORIGIN = 0x02019c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_104 : ORIGIN = 0x0201a000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_105 : ORIGIN = 0x0201a400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_106 : ORIGIN = 0x0201a800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_107 : ORIGIN = 0x0201ac00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_108 : ORIGIN = 0x0201b000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_109 : ORIGIN = 0x0201b400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_110 : ORIGIN = 0x0201b800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_111 : ORIGIN = 0x0201bc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_112 : ORIGIN = 0x0201c000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_113 : ORIGIN = 0x0201c400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_114 : ORIGIN = 0x0201c800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_115 : ORIGIN = 0x0201cc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_116 : ORIGIN = 0x0201d000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_117 : ORIGIN = 0x0201d400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_118 : ORIGIN = 0x0201d800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_119 : ORIGIN = 0x0201dc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_120 : ORIGIN = 0x0201e000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_121 : ORIGIN = 0x0201e400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_122 : ORIGIN = 0x0201e800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_123 : ORIGIN = 0x0201ec00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_124 : ORIGIN = 0x0201f000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_125 : ORIGIN = 0x0201f400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_126 : ORIGIN = 0x0201f800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_127 : ORIGIN = 0x0201fc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_128 : ORIGIN = 0x02020000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_129 : ORIGIN = 0x02020400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_130 : ORIGIN = 0x02020800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_131 : ORIGIN = 0x02020c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_132 : ORIGIN = 0x02021000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_133 : ORIGIN = 0x02021400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_134 : ORIGIN = 0x02021800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_135 : ORIGIN = 0x02021c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_136 : ORIGIN = 0x02022000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_137 : ORIGIN = 0x02022400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_138 : ORIGIN = 0x02022800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_139 : ORIGIN = 0x02022c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_140 : ORIGIN = 0x02023000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_141 : ORIGIN = 0x02023400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_142 : ORIGIN = 0x02023800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_143 : ORIGIN = 0x02023c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_144 : ORIGIN = 0x02024000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_145 : ORIGIN = 0x02024400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_146 : ORIGIN = 0x02024800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_147 : ORIGIN = 0x02024c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_148 : ORIGIN = 0x02025000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_149 : ORIGIN = 0x02025400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_150 : ORIGIN = 0x02025800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_151 : ORIGIN = 0x02025c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_152 : ORIGIN = 0x02026000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_153 : ORIGIN = 0x02026400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_154 : ORIGIN = 0x02026800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_155 : ORIGIN = 0x02026c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_156 : ORIGIN = 0x02027000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_157 : ORIGIN = 0x02027400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_158 : ORIGIN = 0x02027800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_159 : ORIGIN = 0x02027c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_160 : ORIGIN = 0x02028000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_161 : ORIGIN = 0x02028400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_162 : ORIGIN = 0x02028800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_163 : ORIGIN = 0x02028c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_164 : ORIGIN = 0x02029000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_165 : ORIGIN = 0x02029400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_166 : ORIGIN = 0x02029800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_167 : ORIGIN = 0x02029c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_168 : ORIGIN = 0x0202a000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_169 : ORIGIN = 0x0202a400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_170 : ORIGIN = 0x0202a800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_171 : ORIGIN = 0x0202ac00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_172 : ORIGIN = 0x0202b000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_173 : ORIGIN = 0x0202b400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_174 : ORIGIN = 0x0202b800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_175 : ORIGIN = 0x0202bc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_176 : ORIGIN = 0x0202c000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_177 : ORIGIN = 0x0202c400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_178 : ORIGIN = 0x0202c800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_179 : ORIGIN = 0x0202cc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_180 : ORIGIN = 0x0202d000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_181 : ORIGIN = 0x0202d400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_182 : ORIGIN = 0x0202d800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_183 : ORIGIN = 0x0202dc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_184 : ORIGIN = 0x0202e000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_185 : ORIGIN = 0x0202e400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_186 : ORIGIN = 0x0202e800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_187 : ORIGIN = 0x0202ec00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_188 : ORIGIN = 0x0202f000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_189 : ORIGIN = 0x0202f400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_190 : ORIGIN = 0x0202f800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_191 : ORIGIN = 0x0202fc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_192 : ORIGIN = 0x02030000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_193 : ORIGIN = 0x02030400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_194 : ORIGIN = 0x02030800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_195 : ORIGIN = 0x02030c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_196 : ORIGIN = 0x02031000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_197 : ORIGIN = 0x02031400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_198 : ORIGIN = 0x02031800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_199 : ORIGIN = 0x02031c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_200 : ORIGIN = 0x02032000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_201 : ORIGIN = 0x02032400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_202 : ORIGIN = 0x02032800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_203 : ORIGIN = 0x02032c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_204 : ORIGIN = 0x02033000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_205 : ORIGIN = 0x02033400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_206 : ORIGIN = 0x02033800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_207 : ORIGIN = 0x02033c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_208 : ORIGIN = 0x02034000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_209 : ORIGIN = 0x02034400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_210 : ORIGIN = 0x02034800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_211 : ORIGIN = 0x02034c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_212 : ORIGIN = 0x02035000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_213 : ORIGIN = 0x02035400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_214 : ORIGIN = 0x02035800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_215 : ORIGIN = 0x02035c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_216 : ORIGIN = 0x02036000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_217 : ORIGIN = 0x02036400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_218 : ORIGIN = 0x02036800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_219 : ORIGIN = 0x02036c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_220 : ORIGIN = 0x02037000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_221 : ORIGIN = 0x02037400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_222 : ORIGIN = 0x02037800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_223 : ORIGIN = 0x02037c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_224 : ORIGIN = 0x02038000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_225 : ORIGIN = 0x02038400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_226 : ORIGIN = 0x02038800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_227 : ORIGIN = 0x02038c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_228 : ORIGIN = 0x02039000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_229 : ORIGIN = 0x02039400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_230 : ORIGIN = 0x02039800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_231 : ORIGIN = 0x02039c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_232 : ORIGIN = 0x0203a000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_233 : ORIGIN = 0x0203a400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_234 : ORIGIN = 0x0203a800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_235 : ORIGIN = 0x0203ac00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_236 : ORIGIN = 0x0203b000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_237 : ORIGIN = 0x0203b400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_238 : ORIGIN = 0x0203b800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_239 : ORIGIN = 0x0203bc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_240 : ORIGIN = 0x0203c000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_241 : ORIGIN = 0x0203c400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_242 : ORIGIN = 0x0203c800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_243 : ORIGIN = 0x0203cc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_244 : ORIGIN = 0x0203d000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_245 : ORIGIN = 0x0203d400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_246 : ORIGIN = 0x0203d800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_247 : ORIGIN = 0x0203dc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_248 : ORIGIN = 0x0203e000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_249 : ORIGIN = 0x0203e400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_250 : ORIGIN = 0x0203e800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_251 : ORIGIN = 0x0203ec00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_252 : ORIGIN = 0x0203f000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_253 : ORIGIN = 0x0203f400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_254 : ORIGIN = 0x0203f800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_255 : ORIGIN = 0x0203fc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0

  chr_rom_0_1     : ORIGIN = 0x02000000, LENGTH = __chr_rom_size >= 1   ? 0x800 : 0
  chr_rom_2_3     : ORIGIN = 0x02000800, LENGTH = __chr_rom_size >= 2   ? 0x800 : 0
  chr_rom_4_5     : ORIGIN = 0x02001000, LENGTH = __chr_rom_size >= 4   ? 0x800 : 0
  chr_rom_6_7     : ORIGIN = 0x02001800, LENGTH = __chr_rom_size >= 8   ? 0x800 : 0
  chr_rom_8_9     : ORIGIN = 0x02002000, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_10_11   : ORIGIN = 0x02002800, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_12_13   : ORIGIN = 0x02003000, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_14_15   : ORIGIN = 0x02003800, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_16_17   : ORIGIN = 0x02004000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_18_19   : ORIGIN = 0x02004800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_20_21   : ORIGIN = 0x02005000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_22_23   : ORIGIN = 0x02005800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_24_25   : ORIGIN = 0x02006000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_26_27   : ORIGIN = 0x02006800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_28_29   : ORIGIN = 0x02007000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_30_31   : ORIGIN = 0x02007800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_32_33   : ORIGIN = 0x02008000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_34_35   : ORIGIN = 0x02008800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_36_37   : ORIGIN = 0x02009000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_38_39   : ORIGIN = 0x02009800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_40_41   : ORIGIN = 0x0200a000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_42_43   : ORIGIN = 0x0200a800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_44_45   : ORIGIN = 0x0200b000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_46_47   : ORIGIN = 0x0200b800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_48_49   : ORIGIN = 0x0200c000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_50_51   : ORIGIN = 0x0200c800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_52_53   : ORIGIN = 0x0200d000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_54_55   : ORIGIN = 0x0200d800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_56_57   : ORIGIN = 0x0200e000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_58_59   : ORIGIN = 0x0200e800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_60_61   : ORIGIN = 0x0200f000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_62_63   : ORIGIN = 0x0200f800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_64_65   : ORIGIN = 0x02010000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_66_67   : ORIGIN = 0x02010800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_68_69   : ORIGIN = 0x02011000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_70_71   : ORIGIN = 0x02011800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_72_73   : ORIGIN = 0x02012000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_74_75   : ORIGIN = 0x02012800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_76_77   : ORIGIN = 0x02013000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_78_79   : ORIGIN = 0x02013800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_80_81   : ORIGIN = 0x02014000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_82_83   : ORIGIN = 0x02014800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_84_85   : ORIGIN = 0x02015000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_86_87   : ORIGIN = 0x02015800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_88_89   : ORIGIN = 0x02016000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_90_91   : ORIGIN = 0x02016800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_92_93   : ORIGIN = 0x02017000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_94_95   : ORIGIN = 0x02017800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_96_97   : ORIGIN = 0x02018000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_98_99   : ORIGIN = 0x02018800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_100_101 : ORIGIN = 0x02019000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_102_103 : ORIGIN = 0x02019800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_104_105 : ORIGIN = 0x0201a000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_106_107 : ORIGIN = 0x0201a800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_108_109 : ORIGIN = 0x0201b000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_110_111 : ORIGIN = 0x0201b800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_112_113 : ORIGIN = 0x0201c000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_114_115 : ORIGIN = 0x0201c800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_116_117 : ORIGIN = 0x0201d000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_118_119 : ORIGIN = 0x0201d800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_120_121 : ORIGIN = 0x0201e000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_122_123 : ORIGIN = 0x0201e800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_124_125 : ORIGIN = 0x0201f000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_126_127 : ORIGIN = 0x0201f800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_128_129 : ORIGIN = 0x02020000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_130_131 : ORIGIN = 0x02020800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_132_133 : ORIGIN = 0x02021000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_134_135 : ORIGIN = 0x02021800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_136_137 : ORIGIN = 0x02022000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_138_139 : ORIGIN = 0x02022800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_140_141 : ORIGIN = 0x02023000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_142_143 : ORIGIN = 0x02023800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_144_145 : ORIGIN = 0x02024000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_146_147 : ORIGIN = 0x02024800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_148_149 : ORIGIN = 0x02025000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_150_151 : ORIGIN = 0x02025800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_152_153 : ORIGIN = 0x02026000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_154_155 : ORIGIN = 0x02026800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_156_157 : ORIGIN = 0x02027000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_158_159 : ORIGIN = 0x02027800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_160_161 : ORIGIN = 0x02028000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_162_163 : ORIGIN = 0x02028800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_164_165 : ORIGIN = 0x02029000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_166_167 : ORIGIN = 0x02029800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_168_169 : ORIGIN = 0x0202a000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_170_171 : ORIGIN = 0x0202a800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_172_173 : ORIGIN = 0x0202b000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_174_175 : ORIGIN = 0x0202b800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_176_177 : ORIGIN = 0x0202c000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_178_179 : ORIGIN = 0x0202c800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_180_181 : ORIGIN = 0x0202d000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_182_183 : ORIGIN = 0x0202d800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_184_185 : ORIGIN = 0x0202e000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_186_187 : ORIGIN = 0x0202e800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_188_189 : ORIGIN = 0x0202f000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_190_191 : ORIGIN = 0x0202f800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_192_193 : ORIGIN = 0x02030000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_194_195 : ORIGIN = 0x02030800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_196_197 : ORIGIN = 0x02031000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_198_199 : ORIGIN = 0x02031800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_200_201 : ORIGIN = 0x02032000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_202_203 : ORIGIN = 0x02032800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_204_205 : ORIGIN = 0x02033000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_206_207 : ORIGIN = 0x02033800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_208_209 : ORIGIN = 0x02034000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_210_211 : ORIGIN = 0x02034800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_212_213 : ORIGIN = 0x02035000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_214_215 : ORIGIN = 0x02035800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_216_217 : ORIGIN = 0x02036000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_218_219 : ORIGIN = 0x02036800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_220_221 : ORIGIN = 0x02037000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_222_223 : ORIGIN = 0x02037800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_224_225 : ORIGIN = 0x02038000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_226_227 : ORIGIN = 0x02038800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_228_229 : ORIGIN = 0x02039000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_230_231 : ORIGIN = 0x02039800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_232_233 : ORIGIN = 0x0203a000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_234_235 : ORIGIN = 0x0203a800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_236_237 : ORIGIN = 0x0203b000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_238_239 : ORIGIN = 0x0203b800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_240_241 : ORIGIN = 0x0203c000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_242_243 : ORIGIN = 0x0203c800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_244_245 : ORIGIN = 0x0203d000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_246_247 : ORIGIN = 0x0203d800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_248_249 : ORIGIN = 0x0203e000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_250_251 : ORIGIN = 0x0203e800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_252_253 : ORIGIN = 0x0203f000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_254_255 : ORIGIN = 0x0203f800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram_vma AT>prg_ram_lma

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
  .prg_rom_15    : { *(.prg_rom_15    .prg_rom_15.*)    } >prg_rom_15_vma    AT>prg_rom_15_lma
  .prg_rom_16    : { *(.prg_rom_16    .prg_rom_16.*)    } >prg_rom_16_vma    AT>prg_rom_16_lma
  .prg_rom_17    : { *(.prg_rom_17    .prg_rom_17.*)    } >prg_rom_17_vma    AT>prg_rom_17_lma
  .prg_rom_18    : { *(.prg_rom_18    .prg_rom_18.*)    } >prg_rom_18_vma    AT>prg_rom_18_lma
  .prg_rom_19    : { *(.prg_rom_19    .prg_rom_19.*)    } >prg_rom_19_vma    AT>prg_rom_19_lma
  .prg_rom_20    : { *(.prg_rom_20    .prg_rom_20.*)    } >prg_rom_20_vma    AT>prg_rom_20_lma
  .prg_rom_21    : { *(.prg_rom_21    .prg_rom_21.*)    } >prg_rom_21_vma    AT>prg_rom_21_lma
  .prg_rom_22    : { *(.prg_rom_22    .prg_rom_22.*)    } >prg_rom_22_vma    AT>prg_rom_22_lma
  .prg_rom_23    : { *(.prg_rom_23    .prg_rom_23.*)    } >prg_rom_23_vma    AT>prg_rom_23_lma
  .prg_rom_24    : { *(.prg_rom_24    .prg_rom_24.*)    } >prg_rom_24_vma    AT>prg_rom_24_lma
  .prg_rom_25    : { *(.prg_rom_25    .prg_rom_25.*)    } >prg_rom_25_vma    AT>prg_rom_25_lma
  .prg_rom_26    : { *(.prg_rom_26    .prg_rom_26.*)    } >prg_rom_26_vma    AT>prg_rom_26_lma
  .prg_rom_27    : { *(.prg_rom_27    .prg_rom_27.*)    } >prg_rom_27_vma    AT>prg_rom_27_lma
  .prg_rom_28    : { *(.prg_rom_28    .prg_rom_28.*)    } >prg_rom_28_vma    AT>prg_rom_28_lma
  .prg_rom_29    : { *(.prg_rom_29    .prg_rom_29.*)    } >prg_rom_29_vma    AT>prg_rom_29_lma
  .prg_rom_30    : { *(.prg_rom_30    .prg_rom_30.*)    } >prg_rom_30_vma    AT>prg_rom_30_lma
  .prg_rom_31    : { *(.prg_rom_31    .prg_rom_31.*)    } >prg_rom_31_vma    AT>prg_rom_31_lma
  .prg_rom_32    : { *(.prg_rom_32    .prg_rom_32.*)    } >prg_rom_32_vma    AT>prg_rom_32_lma
  .prg_rom_33    : { *(.prg_rom_33    .prg_rom_33.*)    } >prg_rom_33_vma    AT>prg_rom_33_lma
  .prg_rom_34    : { *(.prg_rom_34    .prg_rom_34.*)    } >prg_rom_34_vma    AT>prg_rom_34_lma
  .prg_rom_35    : { *(.prg_rom_35    .prg_rom_35.*)    } >prg_rom_35_vma    AT>prg_rom_35_lma
  .prg_rom_36    : { *(.prg_rom_36    .prg_rom_36.*)    } >prg_rom_36_vma    AT>prg_rom_36_lma
  .prg_rom_37    : { *(.prg_rom_37    .prg_rom_37.*)    } >prg_rom_37_vma    AT>prg_rom_37_lma
  .prg_rom_38    : { *(.prg_rom_38    .prg_rom_38.*)    } >prg_rom_38_vma    AT>prg_rom_38_lma
  .prg_rom_39    : { *(.prg_rom_39    .prg_rom_39.*)    } >prg_rom_39_vma    AT>prg_rom_39_lma
  .prg_rom_40    : { *(.prg_rom_40    .prg_rom_40.*)    } >prg_rom_40_vma    AT>prg_rom_40_lma
  .prg_rom_41    : { *(.prg_rom_41    .prg_rom_41.*)    } >prg_rom_41_vma    AT>prg_rom_41_lma
  .prg_rom_42    : { *(.prg_rom_42    .prg_rom_42.*)    } >prg_rom_42_vma    AT>prg_rom_42_lma
  .prg_rom_43    : { *(.prg_rom_43    .prg_rom_43.*)    } >prg_rom_43_vma    AT>prg_rom_43_lma
  .prg_rom_44    : { *(.prg_rom_44    .prg_rom_44.*)    } >prg_rom_44_vma    AT>prg_rom_44_lma
  .prg_rom_45    : { *(.prg_rom_45    .prg_rom_45.*)    } >prg_rom_45_vma    AT>prg_rom_45_lma
  .prg_rom_46    : { *(.prg_rom_46    .prg_rom_46.*)    } >prg_rom_46_vma    AT>prg_rom_46_lma
  .prg_rom_47    : { *(.prg_rom_47    .prg_rom_47.*)    } >prg_rom_47_vma    AT>prg_rom_47_lma
  .prg_rom_48    : { *(.prg_rom_48    .prg_rom_48.*)    } >prg_rom_48_vma    AT>prg_rom_48_lma
  .prg_rom_49    : { *(.prg_rom_49    .prg_rom_49.*)    } >prg_rom_49_vma    AT>prg_rom_49_lma
  .prg_rom_50    : { *(.prg_rom_50    .prg_rom_50.*)    } >prg_rom_50_vma    AT>prg_rom_50_lma
  .prg_rom_51    : { *(.prg_rom_51    .prg_rom_51.*)    } >prg_rom_51_vma    AT>prg_rom_51_lma
  .prg_rom_52    : { *(.prg_rom_52    .prg_rom_52.*)    } >prg_rom_52_vma    AT>prg_rom_52_lma
  .prg_rom_53    : { *(.prg_rom_53    .prg_rom_53.*)    } >prg_rom_53_vma    AT>prg_rom_53_lma
  .prg_rom_54    : { *(.prg_rom_54    .prg_rom_54.*)    } >prg_rom_54_vma    AT>prg_rom_54_lma
  .prg_rom_55    : { *(.prg_rom_55    .prg_rom_55.*)    } >prg_rom_55_vma    AT>prg_rom_55_lma
  .prg_rom_56    : { *(.prg_rom_56    .prg_rom_56.*)    } >prg_rom_56_vma    AT>prg_rom_56_lma
  .prg_rom_57    : { *(.prg_rom_57    .prg_rom_57.*)    } >prg_rom_57_vma    AT>prg_rom_57_lma
  .prg_rom_58    : { *(.prg_rom_58    .prg_rom_58.*)    } >prg_rom_58_vma    AT>prg_rom_58_lma
  .prg_rom_59    : { *(.prg_rom_59    .prg_rom_59.*)    } >prg_rom_59_vma    AT>prg_rom_59_lma
  .prg_rom_60    : { *(.prg_rom_60    .prg_rom_60.*)    } >prg_rom_60_vma    AT>prg_rom_60_lma
  .prg_rom_61    : { *(.prg_rom_61    .prg_rom_61.*)    } >prg_rom_61_vma    AT>prg_rom_61_lma
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed_vma AT>prg_rom_fixed_lma

  .chr_rom_0   : { KEEP(*(.chr_rom_0   .chr_rom_0.*)) }   >chr_rom_0
  .chr_rom_1   : { KEEP(*(.chr_rom_1   .chr_rom_1.*)) }   >chr_rom_1
  .chr_rom_2   : { KEEP(*(.chr_rom_2   .chr_rom_2.*)) }   >chr_rom_2
  .chr_rom_3   : { KEEP(*(.chr_rom_3   .chr_rom_3.*)) }   >chr_rom_3
  .chr_rom_4   : { KEEP(*(.chr_rom_4   .chr_rom_4.*)) }   >chr_rom_4
  .chr_rom_5   : { KEEP(*(.chr_rom_5   .chr_rom_5.*)) }   >chr_rom_5
  .chr_rom_6   : { KEEP(*(.chr_rom_6   .chr_rom_6.*)) }   >chr_rom_6
  .chr_rom_7   : { KEEP(*(.chr_rom_7   .chr_rom_7.*)) }   >chr_rom_7
  .chr_rom_8   : { KEEP(*(.chr_rom_8   .chr_rom_8.*)) }   >chr_rom_8
  .chr_rom_9   : { KEEP(*(.chr_rom_9   .chr_rom_9.*)) }   >chr_rom_9
  .chr_rom_10  : { KEEP(*(.chr_rom_10  .chr_rom_10.*)) }  >chr_rom_10
  .chr_rom_11  : { KEEP(*(.chr_rom_11  .chr_rom_11.*)) }  >chr_rom_11
  .chr_rom_12  : { KEEP(*(.chr_rom_12  .chr_rom_12.*)) }  >chr_rom_12
  .chr_rom_13  : { KEEP(*(.chr_rom_13  .chr_rom_13.*)) }  >chr_rom_13
  .chr_rom_14  : { KEEP(*(.chr_rom_14  .chr_rom_14.*)) }  >chr_rom_14
  .chr_rom_15  : { KEEP(*(.chr_rom_15  .chr_rom_15.*)) }  >chr_rom_15
  .chr_rom_16  : { KEEP(*(.chr_rom_16  .chr_rom_16.*)) }  >chr_rom_16
  .chr_rom_17  : { KEEP(*(.chr_rom_17  .chr_rom_17.*)) }  >chr_rom_17
  .chr_rom_18  : { KEEP(*(.chr_rom_18  .chr_rom_18.*)) }  >chr_rom_18
  .chr_rom_19  : { KEEP(*(.chr_rom_19  .chr_rom_19.*)) }  >chr_rom_19
  .chr_rom_20  : { KEEP(*(.chr_rom_20  .chr_rom_20.*)) }  >chr_rom_20
  .chr_rom_21  : { KEEP(*(.chr_rom_21  .chr_rom_21.*)) }  >chr_rom_21
  .chr_rom_22  : { KEEP(*(.chr_rom_22  .chr_rom_22.*)) }  >chr_rom_22
  .chr_rom_23  : { KEEP(*(.chr_rom_23  .chr_rom_23.*)) }  >chr_rom_23
  .chr_rom_24  : { KEEP(*(.chr_rom_24  .chr_rom_24.*)) }  >chr_rom_24
  .chr_rom_25  : { KEEP(*(.chr_rom_25  .chr_rom_25.*)) }  >chr_rom_25
  .chr_rom_26  : { KEEP(*(.chr_rom_26  .chr_rom_26.*)) }  >chr_rom_26
  .chr_rom_27  : { KEEP(*(.chr_rom_27  .chr_rom_27.*)) }  >chr_rom_27
  .chr_rom_28  : { KEEP(*(.chr_rom_28  .chr_rom_28.*)) }  >chr_rom_28
  .chr_rom_29  : { KEEP(*(.chr_rom_29  .chr_rom_29.*)) }  >chr_rom_29
  .chr_rom_30  : { KEEP(*(.chr_rom_30  .chr_rom_30.*)) }  >chr_rom_30
  .chr_rom_31  : { KEEP(*(.chr_rom_31  .chr_rom_31.*)) }  >chr_rom_31
  .chr_rom_32  : { KEEP(*(.chr_rom_32  .chr_rom_32.*)) }  >chr_rom_32
  .chr_rom_33  : { KEEP(*(.chr_rom_33  .chr_rom_33.*)) }  >chr_rom_33
  .chr_rom_34  : { KEEP(*(.chr_rom_34  .chr_rom_34.*)) }  >chr_rom_34
  .chr_rom_35  : { KEEP(*(.chr_rom_35  .chr_rom_35.*)) }  >chr_rom_35
  .chr_rom_36  : { KEEP(*(.chr_rom_36  .chr_rom_36.*)) }  >chr_rom_36
  .chr_rom_37  : { KEEP(*(.chr_rom_37  .chr_rom_37.*)) }  >chr_rom_37
  .chr_rom_38  : { KEEP(*(.chr_rom_38  .chr_rom_38.*)) }  >chr_rom_38
  .chr_rom_39  : { KEEP(*(.chr_rom_39  .chr_rom_39.*)) }  >chr_rom_39
  .chr_rom_40  : { KEEP(*(.chr_rom_40  .chr_rom_40.*)) }  >chr_rom_40
  .chr_rom_41  : { KEEP(*(.chr_rom_41  .chr_rom_41.*)) }  >chr_rom_41
  .chr_rom_42  : { KEEP(*(.chr_rom_42  .chr_rom_42.*)) }  >chr_rom_42
  .chr_rom_43  : { KEEP(*(.chr_rom_43  .chr_rom_43.*)) }  >chr_rom_43
  .chr_rom_44  : { KEEP(*(.chr_rom_44  .chr_rom_44.*)) }  >chr_rom_44
  .chr_rom_45  : { KEEP(*(.chr_rom_45  .chr_rom_45.*)) }  >chr_rom_45
  .chr_rom_46  : { KEEP(*(.chr_rom_46  .chr_rom_46.*)) }  >chr_rom_46
  .chr_rom_47  : { KEEP(*(.chr_rom_47  .chr_rom_47.*)) }  >chr_rom_47
  .chr_rom_48  : { KEEP(*(.chr_rom_48  .chr_rom_48.*)) }  >chr_rom_48
  .chr_rom_49  : { KEEP(*(.chr_rom_49  .chr_rom_49.*)) }  >chr_rom_49
  .chr_rom_50  : { KEEP(*(.chr_rom_50  .chr_rom_50.*)) }  >chr_rom_50
  .chr_rom_51  : { KEEP(*(.chr_rom_51  .chr_rom_51.*)) }  >chr_rom_51
  .chr_rom_52  : { KEEP(*(.chr_rom_52  .chr_rom_52.*)) }  >chr_rom_52
  .chr_rom_53  : { KEEP(*(.chr_rom_53  .chr_rom_53.*)) }  >chr_rom_53
  .chr_rom_54  : { KEEP(*(.chr_rom_54  .chr_rom_54.*)) }  >chr_rom_54
  .chr_rom_55  : { KEEP(*(.chr_rom_55  .chr_rom_55.*)) }  >chr_rom_55
  .chr_rom_56  : { KEEP(*(.chr_rom_56  .chr_rom_56.*)) }  >chr_rom_56
  .chr_rom_57  : { KEEP(*(.chr_rom_57  .chr_rom_57.*)) }  >chr_rom_57
  .chr_rom_58  : { KEEP(*(.chr_rom_58  .chr_rom_58.*)) }  >chr_rom_58
  .chr_rom_59  : { KEEP(*(.chr_rom_59  .chr_rom_59.*)) }  >chr_rom_59
  .chr_rom_60  : { KEEP(*(.chr_rom_60  .chr_rom_60.*)) }  >chr_rom_60
  .chr_rom_61  : { KEEP(*(.chr_rom_61  .chr_rom_61.*)) }  >chr_rom_61
  .chr_rom_62  : { KEEP(*(.chr_rom_62  .chr_rom_62.*)) }  >chr_rom_62
  .chr_rom_63  : { KEEP(*(.chr_rom_63  .chr_rom_63.*)) }  >chr_rom_63
  .chr_rom_64  : { KEEP(*(.chr_rom_64  .chr_rom_64.*)) }  >chr_rom_64
  .chr_rom_65  : { KEEP(*(.chr_rom_65  .chr_rom_65.*)) }  >chr_rom_65
  .chr_rom_66  : { KEEP(*(.chr_rom_66  .chr_rom_66.*)) }  >chr_rom_66
  .chr_rom_67  : { KEEP(*(.chr_rom_67  .chr_rom_67.*)) }  >chr_rom_67
  .chr_rom_68  : { KEEP(*(.chr_rom_68  .chr_rom_68.*)) }  >chr_rom_68
  .chr_rom_69  : { KEEP(*(.chr_rom_69  .chr_rom_69.*)) }  >chr_rom_69
  .chr_rom_70  : { KEEP(*(.chr_rom_70  .chr_rom_70.*)) }  >chr_rom_70
  .chr_rom_71  : { KEEP(*(.chr_rom_71  .chr_rom_71.*)) }  >chr_rom_71
  .chr_rom_72  : { KEEP(*(.chr_rom_72  .chr_rom_72.*)) }  >chr_rom_72
  .chr_rom_73  : { KEEP(*(.chr_rom_73  .chr_rom_73.*)) }  >chr_rom_73
  .chr_rom_74  : { KEEP(*(.chr_rom_74  .chr_rom_74.*)) }  >chr_rom_74
  .chr_rom_75  : { KEEP(*(.chr_rom_75  .chr_rom_75.*)) }  >chr_rom_75
  .chr_rom_76  : { KEEP(*(.chr_rom_76  .chr_rom_76.*)) }  >chr_rom_76
  .chr_rom_77  : { KEEP(*(.chr_rom_77  .chr_rom_77.*)) }  >chr_rom_77
  .chr_rom_78  : { KEEP(*(.chr_rom_78  .chr_rom_78.*)) }  >chr_rom_78
  .chr_rom_79  : { KEEP(*(.chr_rom_79  .chr_rom_79.*)) }  >chr_rom_79
  .chr_rom_80  : { KEEP(*(.chr_rom_80  .chr_rom_80.*)) }  >chr_rom_80
  .chr_rom_81  : { KEEP(*(.chr_rom_81  .chr_rom_81.*)) }  >chr_rom_81
  .chr_rom_82  : { KEEP(*(.chr_rom_82  .chr_rom_82.*)) }  >chr_rom_82
  .chr_rom_83  : { KEEP(*(.chr_rom_83  .chr_rom_83.*)) }  >chr_rom_83
  .chr_rom_84  : { KEEP(*(.chr_rom_84  .chr_rom_84.*)) }  >chr_rom_84
  .chr_rom_85  : { KEEP(*(.chr_rom_85  .chr_rom_85.*)) }  >chr_rom_85
  .chr_rom_86  : { KEEP(*(.chr_rom_86  .chr_rom_86.*)) }  >chr_rom_86
  .chr_rom_87  : { KEEP(*(.chr_rom_87  .chr_rom_87.*)) }  >chr_rom_87
  .chr_rom_88  : { KEEP(*(.chr_rom_88  .chr_rom_88.*)) }  >chr_rom_88
  .chr_rom_89  : { KEEP(*(.chr_rom_89  .chr_rom_89.*)) }  >chr_rom_89
  .chr_rom_90  : { KEEP(*(.chr_rom_90  .chr_rom_90.*)) }  >chr_rom_90
  .chr_rom_91  : { KEEP(*(.chr_rom_91  .chr_rom_91.*)) }  >chr_rom_91
  .chr_rom_92  : { KEEP(*(.chr_rom_92  .chr_rom_92.*)) }  >chr_rom_92
  .chr_rom_93  : { KEEP(*(.chr_rom_93  .chr_rom_93.*)) }  >chr_rom_93
  .chr_rom_94  : { KEEP(*(.chr_rom_94  .chr_rom_94.*)) }  >chr_rom_94
  .chr_rom_95  : { KEEP(*(.chr_rom_95  .chr_rom_95.*)) }  >chr_rom_95
  .chr_rom_96  : { KEEP(*(.chr_rom_96  .chr_rom_96.*)) }  >chr_rom_96
  .chr_rom_97  : { KEEP(*(.chr_rom_97  .chr_rom_97.*)) }  >chr_rom_97
  .chr_rom_98  : { KEEP(*(.chr_rom_98  .chr_rom_98.*)) }  >chr_rom_98
  .chr_rom_99  : { KEEP(*(.chr_rom_99  .chr_rom_99.*)) }  >chr_rom_99
  .chr_rom_100 : { KEEP(*(.chr_rom_100 .chr_rom_100.*)) } >chr_rom_100
  .chr_rom_101 : { KEEP(*(.chr_rom_101 .chr_rom_101.*)) } >chr_rom_101
  .chr_rom_102 : { KEEP(*(.chr_rom_102 .chr_rom_102.*)) } >chr_rom_102
  .chr_rom_103 : { KEEP(*(.chr_rom_103 .chr_rom_103.*)) } >chr_rom_103
  .chr_rom_104 : { KEEP(*(.chr_rom_104 .chr_rom_104.*)) } >chr_rom_104
  .chr_rom_105 : { KEEP(*(.chr_rom_105 .chr_rom_105.*)) } >chr_rom_105
  .chr_rom_106 : { KEEP(*(.chr_rom_106 .chr_rom_106.*)) } >chr_rom_106
  .chr_rom_107 : { KEEP(*(.chr_rom_107 .chr_rom_107.*)) } >chr_rom_107
  .chr_rom_108 : { KEEP(*(.chr_rom_108 .chr_rom_108.*)) } >chr_rom_108
  .chr_rom_109 : { KEEP(*(.chr_rom_109 .chr_rom_109.*)) } >chr_rom_109
  .chr_rom_110 : { KEEP(*(.chr_rom_110 .chr_rom_110.*)) } >chr_rom_110
  .chr_rom_111 : { KEEP(*(.chr_rom_111 .chr_rom_111.*)) } >chr_rom_111
  .chr_rom_112 : { KEEP(*(.chr_rom_112 .chr_rom_112.*)) } >chr_rom_112
  .chr_rom_113 : { KEEP(*(.chr_rom_113 .chr_rom_113.*)) } >chr_rom_113
  .chr_rom_114 : { KEEP(*(.chr_rom_114 .chr_rom_114.*)) } >chr_rom_114
  .chr_rom_115 : { KEEP(*(.chr_rom_115 .chr_rom_115.*)) } >chr_rom_115
  .chr_rom_116 : { KEEP(*(.chr_rom_116 .chr_rom_116.*)) } >chr_rom_116
  .chr_rom_117 : { KEEP(*(.chr_rom_117 .chr_rom_117.*)) } >chr_rom_117
  .chr_rom_118 : { KEEP(*(.chr_rom_118 .chr_rom_118.*)) } >chr_rom_118
  .chr_rom_119 : { KEEP(*(.chr_rom_119 .chr_rom_119.*)) } >chr_rom_119
  .chr_rom_120 : { KEEP(*(.chr_rom_120 .chr_rom_120.*)) } >chr_rom_120
  .chr_rom_121 : { KEEP(*(.chr_rom_121 .chr_rom_121.*)) } >chr_rom_121
  .chr_rom_122 : { KEEP(*(.chr_rom_122 .chr_rom_122.*)) } >chr_rom_122
  .chr_rom_123 : { KEEP(*(.chr_rom_123 .chr_rom_123.*)) } >chr_rom_123
  .chr_rom_124 : { KEEP(*(.chr_rom_124 .chr_rom_124.*)) } >chr_rom_124
  .chr_rom_125 : { KEEP(*(.chr_rom_125 .chr_rom_125.*)) } >chr_rom_125
  .chr_rom_126 : { KEEP(*(.chr_rom_126 .chr_rom_126.*)) } >chr_rom_126
  .chr_rom_127 : { KEEP(*(.chr_rom_127 .chr_rom_127.*)) } >chr_rom_127
  .chr_rom_128 : { KEEP(*(.chr_rom_128 .chr_rom_128.*)) } >chr_rom_128
  .chr_rom_129 : { KEEP(*(.chr_rom_129 .chr_rom_129.*)) } >chr_rom_129
  .chr_rom_130 : { KEEP(*(.chr_rom_130 .chr_rom_130.*)) } >chr_rom_130
  .chr_rom_131 : { KEEP(*(.chr_rom_131 .chr_rom_131.*)) } >chr_rom_131
  .chr_rom_132 : { KEEP(*(.chr_rom_132 .chr_rom_132.*)) } >chr_rom_132
  .chr_rom_133 : { KEEP(*(.chr_rom_133 .chr_rom_133.*)) } >chr_rom_133
  .chr_rom_134 : { KEEP(*(.chr_rom_134 .chr_rom_134.*)) } >chr_rom_134
  .chr_rom_135 : { KEEP(*(.chr_rom_135 .chr_rom_135.*)) } >chr_rom_135
  .chr_rom_136 : { KEEP(*(.chr_rom_136 .chr_rom_136.*)) } >chr_rom_136
  .chr_rom_137 : { KEEP(*(.chr_rom_137 .chr_rom_137.*)) } >chr_rom_137
  .chr_rom_138 : { KEEP(*(.chr_rom_138 .chr_rom_138.*)) } >chr_rom_138
  .chr_rom_139 : { KEEP(*(.chr_rom_139 .chr_rom_139.*)) } >chr_rom_139
  .chr_rom_140 : { KEEP(*(.chr_rom_140 .chr_rom_140.*)) } >chr_rom_140
  .chr_rom_141 : { KEEP(*(.chr_rom_141 .chr_rom_141.*)) } >chr_rom_141
  .chr_rom_142 : { KEEP(*(.chr_rom_142 .chr_rom_142.*)) } >chr_rom_142
  .chr_rom_143 : { KEEP(*(.chr_rom_143 .chr_rom_143.*)) } >chr_rom_143
  .chr_rom_144 : { KEEP(*(.chr_rom_144 .chr_rom_144.*)) } >chr_rom_144
  .chr_rom_145 : { KEEP(*(.chr_rom_145 .chr_rom_145.*)) } >chr_rom_145
  .chr_rom_146 : { KEEP(*(.chr_rom_146 .chr_rom_146.*)) } >chr_rom_146
  .chr_rom_147 : { KEEP(*(.chr_rom_147 .chr_rom_147.*)) } >chr_rom_147
  .chr_rom_148 : { KEEP(*(.chr_rom_148 .chr_rom_148.*)) } >chr_rom_148
  .chr_rom_149 : { KEEP(*(.chr_rom_149 .chr_rom_149.*)) } >chr_rom_149
  .chr_rom_150 : { KEEP(*(.chr_rom_150 .chr_rom_150.*)) } >chr_rom_150
  .chr_rom_151 : { KEEP(*(.chr_rom_151 .chr_rom_151.*)) } >chr_rom_151
  .chr_rom_152 : { KEEP(*(.chr_rom_152 .chr_rom_152.*)) } >chr_rom_152
  .chr_rom_153 : { KEEP(*(.chr_rom_153 .chr_rom_153.*)) } >chr_rom_153
  .chr_rom_154 : { KEEP(*(.chr_rom_154 .chr_rom_154.*)) } >chr_rom_154
  .chr_rom_155 : { KEEP(*(.chr_rom_155 .chr_rom_155.*)) } >chr_rom_155
  .chr_rom_156 : { KEEP(*(.chr_rom_156 .chr_rom_156.*)) } >chr_rom_156
  .chr_rom_157 : { KEEP(*(.chr_rom_157 .chr_rom_157.*)) } >chr_rom_157
  .chr_rom_158 : { KEEP(*(.chr_rom_158 .chr_rom_158.*)) } >chr_rom_158
  .chr_rom_159 : { KEEP(*(.chr_rom_159 .chr_rom_159.*)) } >chr_rom_159
  .chr_rom_160 : { KEEP(*(.chr_rom_160 .chr_rom_160.*)) } >chr_rom_160
  .chr_rom_161 : { KEEP(*(.chr_rom_161 .chr_rom_161.*)) } >chr_rom_161
  .chr_rom_162 : { KEEP(*(.chr_rom_162 .chr_rom_162.*)) } >chr_rom_162
  .chr_rom_163 : { KEEP(*(.chr_rom_163 .chr_rom_163.*)) } >chr_rom_163
  .chr_rom_164 : { KEEP(*(.chr_rom_164 .chr_rom_164.*)) } >chr_rom_164
  .chr_rom_165 : { KEEP(*(.chr_rom_165 .chr_rom_165.*)) } >chr_rom_165
  .chr_rom_166 : { KEEP(*(.chr_rom_166 .chr_rom_166.*)) } >chr_rom_166
  .chr_rom_167 : { KEEP(*(.chr_rom_167 .chr_rom_167.*)) } >chr_rom_167
  .chr_rom_168 : { KEEP(*(.chr_rom_168 .chr_rom_168.*)) } >chr_rom_168
  .chr_rom_169 : { KEEP(*(.chr_rom_169 .chr_rom_169.*)) } >chr_rom_169
  .chr_rom_170 : { KEEP(*(.chr_rom_170 .chr_rom_170.*)) } >chr_rom_170
  .chr_rom_171 : { KEEP(*(.chr_rom_171 .chr_rom_171.*)) } >chr_rom_171
  .chr_rom_172 : { KEEP(*(.chr_rom_172 .chr_rom_172.*)) } >chr_rom_172
  .chr_rom_173 : { KEEP(*(.chr_rom_173 .chr_rom_173.*)) } >chr_rom_173
  .chr_rom_174 : { KEEP(*(.chr_rom_174 .chr_rom_174.*)) } >chr_rom_174
  .chr_rom_175 : { KEEP(*(.chr_rom_175 .chr_rom_175.*)) } >chr_rom_175
  .chr_rom_176 : { KEEP(*(.chr_rom_176 .chr_rom_176.*)) } >chr_rom_176
  .chr_rom_177 : { KEEP(*(.chr_rom_177 .chr_rom_177.*)) } >chr_rom_177
  .chr_rom_178 : { KEEP(*(.chr_rom_178 .chr_rom_178.*)) } >chr_rom_178
  .chr_rom_179 : { KEEP(*(.chr_rom_179 .chr_rom_179.*)) } >chr_rom_179
  .chr_rom_180 : { KEEP(*(.chr_rom_180 .chr_rom_180.*)) } >chr_rom_180
  .chr_rom_181 : { KEEP(*(.chr_rom_181 .chr_rom_181.*)) } >chr_rom_181
  .chr_rom_182 : { KEEP(*(.chr_rom_182 .chr_rom_182.*)) } >chr_rom_182
  .chr_rom_183 : { KEEP(*(.chr_rom_183 .chr_rom_183.*)) } >chr_rom_183
  .chr_rom_184 : { KEEP(*(.chr_rom_184 .chr_rom_184.*)) } >chr_rom_184
  .chr_rom_185 : { KEEP(*(.chr_rom_185 .chr_rom_185.*)) } >chr_rom_185
  .chr_rom_186 : { KEEP(*(.chr_rom_186 .chr_rom_186.*)) } >chr_rom_186
  .chr_rom_187 : { KEEP(*(.chr_rom_187 .chr_rom_187.*)) } >chr_rom_187
  .chr_rom_188 : { KEEP(*(.chr_rom_188 .chr_rom_188.*)) } >chr_rom_188
  .chr_rom_189 : { KEEP(*(.chr_rom_189 .chr_rom_189.*)) } >chr_rom_189
  .chr_rom_190 : { KEEP(*(.chr_rom_190 .chr_rom_190.*)) } >chr_rom_190
  .chr_rom_191 : { KEEP(*(.chr_rom_191 .chr_rom_191.*)) } >chr_rom_191
  .chr_rom_192 : { KEEP(*(.chr_rom_192 .chr_rom_192.*)) } >chr_rom_192
  .chr_rom_193 : { KEEP(*(.chr_rom_193 .chr_rom_193.*)) } >chr_rom_193
  .chr_rom_194 : { KEEP(*(.chr_rom_194 .chr_rom_194.*)) } >chr_rom_194
  .chr_rom_195 : { KEEP(*(.chr_rom_195 .chr_rom_195.*)) } >chr_rom_195
  .chr_rom_196 : { KEEP(*(.chr_rom_196 .chr_rom_196.*)) } >chr_rom_196
  .chr_rom_197 : { KEEP(*(.chr_rom_197 .chr_rom_197.*)) } >chr_rom_197
  .chr_rom_198 : { KEEP(*(.chr_rom_198 .chr_rom_198.*)) } >chr_rom_198
  .chr_rom_199 : { KEEP(*(.chr_rom_199 .chr_rom_199.*)) } >chr_rom_199
  .chr_rom_200 : { KEEP(*(.chr_rom_200 .chr_rom_200.*)) } >chr_rom_200
  .chr_rom_201 : { KEEP(*(.chr_rom_201 .chr_rom_201.*)) } >chr_rom_201
  .chr_rom_202 : { KEEP(*(.chr_rom_202 .chr_rom_202.*)) } >chr_rom_202
  .chr_rom_203 : { KEEP(*(.chr_rom_203 .chr_rom_203.*)) } >chr_rom_203
  .chr_rom_204 : { KEEP(*(.chr_rom_204 .chr_rom_204.*)) } >chr_rom_204
  .chr_rom_205 : { KEEP(*(.chr_rom_205 .chr_rom_205.*)) } >chr_rom_205
  .chr_rom_206 : { KEEP(*(.chr_rom_206 .chr_rom_206.*)) } >chr_rom_206
  .chr_rom_207 : { KEEP(*(.chr_rom_207 .chr_rom_207.*)) } >chr_rom_207
  .chr_rom_208 : { KEEP(*(.chr_rom_208 .chr_rom_208.*)) } >chr_rom_208
  .chr_rom_209 : { KEEP(*(.chr_rom_209 .chr_rom_209.*)) } >chr_rom_209
  .chr_rom_210 : { KEEP(*(.chr_rom_210 .chr_rom_210.*)) } >chr_rom_210
  .chr_rom_211 : { KEEP(*(.chr_rom_211 .chr_rom_211.*)) } >chr_rom_211
  .chr_rom_212 : { KEEP(*(.chr_rom_212 .chr_rom_212.*)) } >chr_rom_212
  .chr_rom_213 : { KEEP(*(.chr_rom_213 .chr_rom_213.*)) } >chr_rom_213
  .chr_rom_214 : { KEEP(*(.chr_rom_214 .chr_rom_214.*)) } >chr_rom_214
  .chr_rom_215 : { KEEP(*(.chr_rom_215 .chr_rom_215.*)) } >chr_rom_215
  .chr_rom_216 : { KEEP(*(.chr_rom_216 .chr_rom_216.*)) } >chr_rom_216
  .chr_rom_217 : { KEEP(*(.chr_rom_217 .chr_rom_217.*)) } >chr_rom_217
  .chr_rom_218 : { KEEP(*(.chr_rom_218 .chr_rom_218.*)) } >chr_rom_218
  .chr_rom_219 : { KEEP(*(.chr_rom_219 .chr_rom_219.*)) } >chr_rom_219
  .chr_rom_220 : { KEEP(*(.chr_rom_220 .chr_rom_220.*)) } >chr_rom_220
  .chr_rom_221 : { KEEP(*(.chr_rom_221 .chr_rom_221.*)) } >chr_rom_221
  .chr_rom_222 : { KEEP(*(.chr_rom_222 .chr_rom_222.*)) } >chr_rom_222
  .chr_rom_223 : { KEEP(*(.chr_rom_223 .chr_rom_223.*)) } >chr_rom_223
  .chr_rom_224 : { KEEP(*(.chr_rom_224 .chr_rom_224.*)) } >chr_rom_224
  .chr_rom_225 : { KEEP(*(.chr_rom_225 .chr_rom_225.*)) } >chr_rom_225
  .chr_rom_226 : { KEEP(*(.chr_rom_226 .chr_rom_226.*)) } >chr_rom_226
  .chr_rom_227 : { KEEP(*(.chr_rom_227 .chr_rom_227.*)) } >chr_rom_227
  .chr_rom_228 : { KEEP(*(.chr_rom_228 .chr_rom_228.*)) } >chr_rom_228
  .chr_rom_229 : { KEEP(*(.chr_rom_229 .chr_rom_229.*)) } >chr_rom_229
  .chr_rom_230 : { KEEP(*(.chr_rom_230 .chr_rom_230.*)) } >chr_rom_230
  .chr_rom_231 : { KEEP(*(.chr_rom_231 .chr_rom_231.*)) } >chr_rom_231
  .chr_rom_232 : { KEEP(*(.chr_rom_232 .chr_rom_232.*)) } >chr_rom_232
  .chr_rom_233 : { KEEP(*(.chr_rom_233 .chr_rom_233.*)) } >chr_rom_233
  .chr_rom_234 : { KEEP(*(.chr_rom_234 .chr_rom_234.*)) } >chr_rom_234
  .chr_rom_235 : { KEEP(*(.chr_rom_235 .chr_rom_235.*)) } >chr_rom_235
  .chr_rom_236 : { KEEP(*(.chr_rom_236 .chr_rom_236.*)) } >chr_rom_236
  .chr_rom_237 : { KEEP(*(.chr_rom_237 .chr_rom_237.*)) } >chr_rom_237
  .chr_rom_238 : { KEEP(*(.chr_rom_238 .chr_rom_238.*)) } >chr_rom_238
  .chr_rom_239 : { KEEP(*(.chr_rom_239 .chr_rom_239.*)) } >chr_rom_239
  .chr_rom_240 : { KEEP(*(.chr_rom_240 .chr_rom_240.*)) } >chr_rom_240
  .chr_rom_241 : { KEEP(*(.chr_rom_241 .chr_rom_241.*)) } >chr_rom_241
  .chr_rom_242 : { KEEP(*(.chr_rom_242 .chr_rom_242.*)) } >chr_rom_242
  .chr_rom_243 : { KEEP(*(.chr_rom_243 .chr_rom_243.*)) } >chr_rom_243
  .chr_rom_244 : { KEEP(*(.chr_rom_244 .chr_rom_244.*)) } >chr_rom_244
  .chr_rom_245 : { KEEP(*(.chr_rom_245 .chr_rom_245.*)) } >chr_rom_245
  .chr_rom_246 : { KEEP(*(.chr_rom_246 .chr_rom_246.*)) } >chr_rom_246
  .chr_rom_247 : { KEEP(*(.chr_rom_247 .chr_rom_247.*)) } >chr_rom_247
  .chr_rom_248 : { KEEP(*(.chr_rom_248 .chr_rom_248.*)) } >chr_rom_248
  .chr_rom_249 : { KEEP(*(.chr_rom_249 .chr_rom_249.*)) } >chr_rom_249
  .chr_rom_250 : { KEEP(*(.chr_rom_250 .chr_rom_250.*)) } >chr_rom_250
  .chr_rom_251 : { KEEP(*(.chr_rom_251 .chr_rom_251.*)) } >chr_rom_251
  .chr_rom_252 : { KEEP(*(.chr_rom_252 .chr_rom_252.*)) } >chr_rom_252
  .chr_rom_253 : { KEEP(*(.chr_rom_253 .chr_rom_253.*)) } >chr_rom_253
  .chr_rom_254 : { KEEP(*(.chr_rom_254 .chr_rom_254.*)) } >chr_rom_254
  .chr_rom_255 : { KEEP(*(.chr_rom_255 .chr_rom_255.*)) } >chr_rom_255

  .chr_rom_0_1     : { KEEP(*(.chr_rom_0_1     .chr_rom_0_1.*)) }     >chr_rom_0_1
  .chr_rom_2_3     : { KEEP(*(.chr_rom_2_3     .chr_rom_2_3.*)) }     >chr_rom_2_3
  .chr_rom_4_5     : { KEEP(*(.chr_rom_4_5     .chr_rom_4_5.*)) }     >chr_rom_4_5
  .chr_rom_6_7     : { KEEP(*(.chr_rom_6_7     .chr_rom_6_7.*)) }     >chr_rom_6_7
  .chr_rom_8_9     : { KEEP(*(.chr_rom_8_9     .chr_rom_8_9.*)) }     >chr_rom_8_9
  .chr_rom_10_11   : { KEEP(*(.chr_rom_10_11   .chr_rom_10_11.*)) }   >chr_rom_10_11
  .chr_rom_12_13   : { KEEP(*(.chr_rom_12_13   .chr_rom_12_13.*)) }   >chr_rom_12_13
  .chr_rom_14_15   : { KEEP(*(.chr_rom_14_15   .chr_rom_14_15.*)) }   >chr_rom_14_15
  .chr_rom_16_17   : { KEEP(*(.chr_rom_16_17   .chr_rom_16_17.*)) }   >chr_rom_16_17
  .chr_rom_18_19   : { KEEP(*(.chr_rom_18_19   .chr_rom_18_19.*)) }   >chr_rom_18_19
  .chr_rom_20_21   : { KEEP(*(.chr_rom_20_21   .chr_rom_20_21.*)) }   >chr_rom_20_21
  .chr_rom_22_23   : { KEEP(*(.chr_rom_22_23   .chr_rom_22_23.*)) }   >chr_rom_22_23
  .chr_rom_24_25   : { KEEP(*(.chr_rom_24_25   .chr_rom_24_25.*)) }   >chr_rom_24_25
  .chr_rom_26_27   : { KEEP(*(.chr_rom_26_27   .chr_rom_26_27.*)) }   >chr_rom_26_27
  .chr_rom_28_29   : { KEEP(*(.chr_rom_28_29   .chr_rom_28_29.*)) }   >chr_rom_28_29
  .chr_rom_30_31   : { KEEP(*(.chr_rom_30_31   .chr_rom_30_31.*)) }   >chr_rom_30_31
  .chr_rom_32_33   : { KEEP(*(.chr_rom_32_33   .chr_rom_32_33.*)) }   >chr_rom_32_33
  .chr_rom_34_35   : { KEEP(*(.chr_rom_34_35   .chr_rom_34_35.*)) }   >chr_rom_34_35
  .chr_rom_36_37   : { KEEP(*(.chr_rom_36_37   .chr_rom_36_37.*)) }   >chr_rom_36_37
  .chr_rom_38_39   : { KEEP(*(.chr_rom_38_39   .chr_rom_38_39.*)) }   >chr_rom_38_39
  .chr_rom_40_41   : { KEEP(*(.chr_rom_40_41   .chr_rom_40_41.*)) }   >chr_rom_40_41
  .chr_rom_42_43   : { KEEP(*(.chr_rom_42_43   .chr_rom_42_43.*)) }   >chr_rom_42_43
  .chr_rom_44_45   : { KEEP(*(.chr_rom_44_45   .chr_rom_44_45.*)) }   >chr_rom_44_45
  .chr_rom_46_47   : { KEEP(*(.chr_rom_46_47   .chr_rom_46_47.*)) }   >chr_rom_46_47
  .chr_rom_48_49   : { KEEP(*(.chr_rom_48_49   .chr_rom_48_49.*)) }   >chr_rom_48_49
  .chr_rom_50_51   : { KEEP(*(.chr_rom_50_51   .chr_rom_50_51.*)) }   >chr_rom_50_51
  .chr_rom_52_53   : { KEEP(*(.chr_rom_52_53   .chr_rom_52_53.*)) }   >chr_rom_52_53
  .chr_rom_54_55   : { KEEP(*(.chr_rom_54_55   .chr_rom_54_55.*)) }   >chr_rom_54_55
  .chr_rom_56_57   : { KEEP(*(.chr_rom_56_57   .chr_rom_56_57.*)) }   >chr_rom_56_57
  .chr_rom_58_59   : { KEEP(*(.chr_rom_58_59   .chr_rom_58_59.*)) }   >chr_rom_58_59
  .chr_rom_60_61   : { KEEP(*(.chr_rom_60_61   .chr_rom_60_61.*)) }   >chr_rom_60_61
  .chr_rom_62_63   : { KEEP(*(.chr_rom_62_63   .chr_rom_62_63.*)) }   >chr_rom_62_63
  .chr_rom_64_65   : { KEEP(*(.chr_rom_64_65   .chr_rom_64_65.*)) }   >chr_rom_64_65
  .chr_rom_66_67   : { KEEP(*(.chr_rom_66_67   .chr_rom_66_67.*)) }   >chr_rom_66_67
  .chr_rom_68_69   : { KEEP(*(.chr_rom_68_69   .chr_rom_68_69.*)) }   >chr_rom_68_69
  .chr_rom_70_71   : { KEEP(*(.chr_rom_70_71   .chr_rom_70_71.*)) }   >chr_rom_70_71
  .chr_rom_72_73   : { KEEP(*(.chr_rom_72_73   .chr_rom_72_73.*)) }   >chr_rom_72_73
  .chr_rom_74_75   : { KEEP(*(.chr_rom_74_75   .chr_rom_74_75.*)) }   >chr_rom_74_75
  .chr_rom_76_77   : { KEEP(*(.chr_rom_76_77   .chr_rom_76_77.*)) }   >chr_rom_76_77
  .chr_rom_78_79   : { KEEP(*(.chr_rom_78_79   .chr_rom_78_79.*)) }   >chr_rom_78_79
  .chr_rom_80_81   : { KEEP(*(.chr_rom_80_81   .chr_rom_80_81.*)) }   >chr_rom_80_81
  .chr_rom_82_83   : { KEEP(*(.chr_rom_82_83   .chr_rom_82_83.*)) }   >chr_rom_82_83
  .chr_rom_84_85   : { KEEP(*(.chr_rom_84_85   .chr_rom_84_85.*)) }   >chr_rom_84_85
  .chr_rom_86_87   : { KEEP(*(.chr_rom_86_87   .chr_rom_86_87.*)) }   >chr_rom_86_87
  .chr_rom_88_89   : { KEEP(*(.chr_rom_88_89   .chr_rom_88_89.*)) }   >chr_rom_88_89
  .chr_rom_90_91   : { KEEP(*(.chr_rom_90_91   .chr_rom_90_91.*)) }   >chr_rom_90_91
  .chr_rom_92_93   : { KEEP(*(.chr_rom_92_93   .chr_rom_92_93.*)) }   >chr_rom_92_93
  .chr_rom_94_95   : { KEEP(*(.chr_rom_94_95   .chr_rom_94_95.*)) }   >chr_rom_94_95
  .chr_rom_96_97   : { KEEP(*(.chr_rom_96_97   .chr_rom_96_97.*)) }   >chr_rom_96_97
  .chr_rom_98_99   : { KEEP(*(.chr_rom_98_99   .chr_rom_98_99.*)) }   >chr_rom_98_99
  .chr_rom_100_101 : { KEEP(*(.chr_rom_100_101 .chr_rom_100_101.*)) } >chr_rom_100_101
  .chr_rom_102_103 : { KEEP(*(.chr_rom_102_103 .chr_rom_102_103.*)) } >chr_rom_102_103
  .chr_rom_104_105 : { KEEP(*(.chr_rom_104_105 .chr_rom_104_105.*)) } >chr_rom_104_105
  .chr_rom_106_107 : { KEEP(*(.chr_rom_106_107 .chr_rom_106_107.*)) } >chr_rom_106_107
  .chr_rom_108_109 : { KEEP(*(.chr_rom_108_109 .chr_rom_108_109.*)) } >chr_rom_108_109
  .chr_rom_110_111 : { KEEP(*(.chr_rom_110_111 .chr_rom_110_111.*)) } >chr_rom_110_111
  .chr_rom_112_113 : { KEEP(*(.chr_rom_112_113 .chr_rom_112_113.*)) } >chr_rom_112_113
  .chr_rom_114_115 : { KEEP(*(.chr_rom_114_115 .chr_rom_114_115.*)) } >chr_rom_114_115
  .chr_rom_116_117 : { KEEP(*(.chr_rom_116_117 .chr_rom_116_117.*)) } >chr_rom_116_117
  .chr_rom_118_119 : { KEEP(*(.chr_rom_118_119 .chr_rom_118_119.*)) } >chr_rom_118_119
  .chr_rom_120_121 : { KEEP(*(.chr_rom_120_121 .chr_rom_120_121.*)) } >chr_rom_120_121
  .chr_rom_122_123 : { KEEP(*(.chr_rom_122_123 .chr_rom_122_123.*)) } >chr_rom_122_123
  .chr_rom_124_125 : { KEEP(*(.chr_rom_124_125 .chr_rom_124_125.*)) } >chr_rom_124_125
  .chr_rom_126_127 : { KEEP(*(.chr_rom_126_127 .chr_rom_126_127.*)) } >chr_rom_126_127
  .chr_rom_128_129 : { KEEP(*(.chr_rom_128_129 .chr_rom_128_129.*)) } >chr_rom_128_129
  .chr_rom_130_131 : { KEEP(*(.chr_rom_130_131 .chr_rom_130_131.*)) } >chr_rom_130_131
  .chr_rom_132_133 : { KEEP(*(.chr_rom_132_133 .chr_rom_132_133.*)) } >chr_rom_132_133
  .chr_rom_134_135 : { KEEP(*(.chr_rom_134_135 .chr_rom_134_135.*)) } >chr_rom_134_135
  .chr_rom_136_137 : { KEEP(*(.chr_rom_136_137 .chr_rom_136_137.*)) } >chr_rom_136_137
  .chr_rom_138_139 : { KEEP(*(.chr_rom_138_139 .chr_rom_138_139.*)) } >chr_rom_138_139
  .chr_rom_140_141 : { KEEP(*(.chr_rom_140_141 .chr_rom_140_141.*)) } >chr_rom_140_141
  .chr_rom_142_143 : { KEEP(*(.chr_rom_142_143 .chr_rom_142_143.*)) } >chr_rom_142_143
  .chr_rom_144_145 : { KEEP(*(.chr_rom_144_145 .chr_rom_144_145.*)) } >chr_rom_144_145
  .chr_rom_146_147 : { KEEP(*(.chr_rom_146_147 .chr_rom_146_147.*)) } >chr_rom_146_147
  .chr_rom_148_149 : { KEEP(*(.chr_rom_148_149 .chr_rom_148_149.*)) } >chr_rom_148_149
  .chr_rom_150_151 : { KEEP(*(.chr_rom_150_151 .chr_rom_150_151.*)) } >chr_rom_150_151
  .chr_rom_152_153 : { KEEP(*(.chr_rom_152_153 .chr_rom_152_153.*)) } >chr_rom_152_153
  .chr_rom_154_155 : { KEEP(*(.chr_rom_154_155 .chr_rom_154_155.*)) } >chr_rom_154_155
  .chr_rom_156_157 : { KEEP(*(.chr_rom_156_157 .chr_rom_156_157.*)) } >chr_rom_156_157
  .chr_rom_158_159 : { KEEP(*(.chr_rom_158_159 .chr_rom_158_159.*)) } >chr_rom_158_159
  .chr_rom_160_161 : { KEEP(*(.chr_rom_160_161 .chr_rom_160_161.*)) } >chr_rom_160_161
  .chr_rom_162_163 : { KEEP(*(.chr_rom_162_163 .chr_rom_162_163.*)) } >chr_rom_162_163
  .chr_rom_164_165 : { KEEP(*(.chr_rom_164_165 .chr_rom_164_165.*)) } >chr_rom_164_165
  .chr_rom_166_167 : { KEEP(*(.chr_rom_166_167 .chr_rom_166_167.*)) } >chr_rom_166_167
  .chr_rom_168_169 : { KEEP(*(.chr_rom_168_169 .chr_rom_168_169.*)) } >chr_rom_168_169
  .chr_rom_170_171 : { KEEP(*(.chr_rom_170_171 .chr_rom_170_171.*)) } >chr_rom_170_171
  .chr_rom_172_173 : { KEEP(*(.chr_rom_172_173 .chr_rom_172_173.*)) } >chr_rom_172_173
  .chr_rom_174_175 : { KEEP(*(.chr_rom_174_175 .chr_rom_174_175.*)) } >chr_rom_174_175
  .chr_rom_176_177 : { KEEP(*(.chr_rom_176_177 .chr_rom_176_177.*)) } >chr_rom_176_177
  .chr_rom_178_179 : { KEEP(*(.chr_rom_178_179 .chr_rom_178_179.*)) } >chr_rom_178_179
  .chr_rom_180_181 : { KEEP(*(.chr_rom_180_181 .chr_rom_180_181.*)) } >chr_rom_180_181
  .chr_rom_182_183 : { KEEP(*(.chr_rom_182_183 .chr_rom_182_183.*)) } >chr_rom_182_183
  .chr_rom_184_185 : { KEEP(*(.chr_rom_184_185 .chr_rom_184_185.*)) } >chr_rom_184_185
  .chr_rom_186_187 : { KEEP(*(.chr_rom_186_187 .chr_rom_186_187.*)) } >chr_rom_186_187
  .chr_rom_188_189 : { KEEP(*(.chr_rom_188_189 .chr_rom_188_189.*)) } >chr_rom_188_189
  .chr_rom_190_191 : { KEEP(*(.chr_rom_190_191 .chr_rom_190_191.*)) } >chr_rom_190_191
  .chr_rom_192_193 : { KEEP(*(.chr_rom_192_193 .chr_rom_192_193.*)) } >chr_rom_192_193
  .chr_rom_194_195 : { KEEP(*(.chr_rom_194_195 .chr_rom_194_195.*)) } >chr_rom_194_195
  .chr_rom_196_197 : { KEEP(*(.chr_rom_196_197 .chr_rom_196_197.*)) } >chr_rom_196_197
  .chr_rom_198_199 : { KEEP(*(.chr_rom_198_199 .chr_rom_198_199.*)) } >chr_rom_198_199
  .chr_rom_200_201 : { KEEP(*(.chr_rom_200_201 .chr_rom_200_201.*)) } >chr_rom_200_201
  .chr_rom_202_203 : { KEEP(*(.chr_rom_202_203 .chr_rom_202_203.*)) } >chr_rom_202_203
  .chr_rom_204_205 : { KEEP(*(.chr_rom_204_205 .chr_rom_204_205.*)) } >chr_rom_204_205
  .chr_rom_206_207 : { KEEP(*(.chr_rom_206_207 .chr_rom_206_207.*)) } >chr_rom_206_207
  .chr_rom_208_209 : { KEEP(*(.chr_rom_208_209 .chr_rom_208_209.*)) } >chr_rom_208_209
  .chr_rom_210_211 : { KEEP(*(.chr_rom_210_211 .chr_rom_210_211.*)) } >chr_rom_210_211
  .chr_rom_212_213 : { KEEP(*(.chr_rom_212_213 .chr_rom_212_213.*)) } >chr_rom_212_213
  .chr_rom_214_215 : { KEEP(*(.chr_rom_214_215 .chr_rom_214_215.*)) } >chr_rom_214_215
  .chr_rom_216_217 : { KEEP(*(.chr_rom_216_217 .chr_rom_216_217.*)) } >chr_rom_216_217
  .chr_rom_218_219 : { KEEP(*(.chr_rom_218_219 .chr_rom_218_219.*)) } >chr_rom_218_219
  .chr_rom_220_221 : { KEEP(*(.chr_rom_220_221 .chr_rom_220_221.*)) } >chr_rom_220_221
  .chr_rom_222_223 : { KEEP(*(.chr_rom_222_223 .chr_rom_222_223.*)) } >chr_rom_222_223
  .chr_rom_224_225 : { KEEP(*(.chr_rom_224_225 .chr_rom_224_225.*)) } >chr_rom_224_225
  .chr_rom_226_227 : { KEEP(*(.chr_rom_226_227 .chr_rom_226_227.*)) } >chr_rom_226_227
  .chr_rom_228_229 : { KEEP(*(.chr_rom_228_229 .chr_rom_228_229.*)) } >chr_rom_228_229
  .chr_rom_230_231 : { KEEP(*(.chr_rom_230_231 .chr_rom_230_231.*)) } >chr_rom_230_231
  .chr_rom_232_233 : { KEEP(*(.chr_rom_232_233 .chr_rom_232_233.*)) } >chr_rom_232_233
  .chr_rom_234_235 : { KEEP(*(.chr_rom_234_235 .chr_rom_234_235.*)) } >chr_rom_234_235
  .chr_rom_236_237 : { KEEP(*(.chr_rom_236_237 .chr_rom_236_237.*)) } >chr_rom_236_237
  .chr_rom_238_239 : { KEEP(*(.chr_rom_238_239 .chr_rom_238_239.*)) } >chr_rom_238_239
  .chr_rom_240_241 : { KEEP(*(.chr_rom_240_241 .chr_rom_240_241.*)) } >chr_rom_240_241
  .chr_rom_242_243 : { KEEP(*(.chr_rom_242_243 .chr_rom_242_243.*)) } >chr_rom_242_243
  .chr_rom_244_245 : { KEEP(*(.chr_rom_244_245 .chr_rom_244_245.*)) } >chr_rom_244_245
  .chr_rom_246_247 : { KEEP(*(.chr_rom_246_247 .chr_rom_246_247.*)) } >chr_rom_246_247
  .chr_rom_248_249 : { KEEP(*(.chr_rom_248_249 .chr_rom_248_249.*)) } >chr_rom_248_249
  .chr_rom_250_251 : { KEEP(*(.chr_rom_250_251 .chr_rom_250_251.*)) } >chr_rom_250_251
  .chr_rom_252_253 : { KEEP(*(.chr_rom_252_253 .chr_rom_252_253.*)) } >chr_rom_252_253
  .chr_rom_254_255 : { KEEP(*(.chr_rom_254_255 .chr_rom_254_255.*)) } >chr_rom_254_255
}

INCLUDE ines.ld
