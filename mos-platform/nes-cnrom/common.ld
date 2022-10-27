/* Common elements of NES-CNROM iNES file linker scripts. */

INCLUDE nes.ld
INCLUDE prg-ram-fixed.ld
INCLUDE prg-rom-fixed.ld

ASSERT(__chr_ram_size + __chr_nvram_size + __chr_rom_size <= 2048,
       "CNROM only supports up to 2048 KiB of CHR.")

MEMORY {
  chr_rom_0   : ORIGIN = 0x02000000, LENGTH = __chr_rom_size >= 8    ? 0x2000 : 0
  chr_rom_1   : ORIGIN = 0x02002000, LENGTH = __chr_rom_size >= 16   ? 0x2000 : 0
  chr_rom_2   : ORIGIN = 0x02004000, LENGTH = __chr_rom_size >= 32   ? 0x2000 : 0
  chr_rom_3   : ORIGIN = 0x02006000, LENGTH = __chr_rom_size >= 32   ? 0x2000 : 0
  chr_rom_4   : ORIGIN = 0x02008000, LENGTH = __chr_rom_size >= 64   ? 0x2000 : 0
  chr_rom_5   : ORIGIN = 0x0200a000, LENGTH = __chr_rom_size >= 64   ? 0x2000 : 0
  chr_rom_6   : ORIGIN = 0x0200c000, LENGTH = __chr_rom_size >= 64   ? 0x2000 : 0
  chr_rom_7   : ORIGIN = 0x0200e000, LENGTH = __chr_rom_size >= 64   ? 0x2000 : 0
  chr_rom_8   : ORIGIN = 0x02010000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_9   : ORIGIN = 0x02012000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_10  : ORIGIN = 0x02014000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_11  : ORIGIN = 0x02016000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_12  : ORIGIN = 0x02018000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_13  : ORIGIN = 0x0201a000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_14  : ORIGIN = 0x0201c000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_15  : ORIGIN = 0x0201e000, LENGTH = __chr_rom_size >= 128  ? 0x2000 : 0
  chr_rom_16  : ORIGIN = 0x02020000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_17  : ORIGIN = 0x02022000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_18  : ORIGIN = 0x02024000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_19  : ORIGIN = 0x02026000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_20  : ORIGIN = 0x02028000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_21  : ORIGIN = 0x0202a000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_22  : ORIGIN = 0x0202c000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_23  : ORIGIN = 0x0202e000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_24  : ORIGIN = 0x02030000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_25  : ORIGIN = 0x02032000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_26  : ORIGIN = 0x02034000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_27  : ORIGIN = 0x02036000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_28  : ORIGIN = 0x02038000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_29  : ORIGIN = 0x0203a000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_30  : ORIGIN = 0x0203c000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_31  : ORIGIN = 0x0203e000, LENGTH = __chr_rom_size >= 256  ? 0x2000 : 0
  chr_rom_32  : ORIGIN = 0x02040000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_33  : ORIGIN = 0x02042000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_34  : ORIGIN = 0x02044000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_35  : ORIGIN = 0x02046000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_36  : ORIGIN = 0x02048000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_37  : ORIGIN = 0x0204a000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_38  : ORIGIN = 0x0204c000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_39  : ORIGIN = 0x0204e000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_40  : ORIGIN = 0x02050000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_41  : ORIGIN = 0x02052000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_42  : ORIGIN = 0x02054000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_43  : ORIGIN = 0x02056000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_44  : ORIGIN = 0x02058000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_45  : ORIGIN = 0x0205a000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_46  : ORIGIN = 0x0205c000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_47  : ORIGIN = 0x0205e000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_48  : ORIGIN = 0x02060000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_49  : ORIGIN = 0x02062000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_50  : ORIGIN = 0x02064000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_51  : ORIGIN = 0x02066000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_52  : ORIGIN = 0x02068000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_53  : ORIGIN = 0x0206a000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_54  : ORIGIN = 0x0206c000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_55  : ORIGIN = 0x0206e000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_56  : ORIGIN = 0x02070000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_57  : ORIGIN = 0x02072000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_58  : ORIGIN = 0x02074000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_59  : ORIGIN = 0x02076000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_60  : ORIGIN = 0x02078000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_61  : ORIGIN = 0x0207a000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_62  : ORIGIN = 0x0207c000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_63  : ORIGIN = 0x0207e000, LENGTH = __chr_rom_size >= 512  ? 0x2000 : 0
  chr_rom_64  : ORIGIN = 0x02080000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_65  : ORIGIN = 0x02082000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_66  : ORIGIN = 0x02084000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_67  : ORIGIN = 0x02086000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_68  : ORIGIN = 0x02088000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_69  : ORIGIN = 0x0208a000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_70  : ORIGIN = 0x0208c000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_71  : ORIGIN = 0x0208e000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_72  : ORIGIN = 0x02090000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_73  : ORIGIN = 0x02092000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_74  : ORIGIN = 0x02094000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_75  : ORIGIN = 0x02096000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_76  : ORIGIN = 0x02098000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_77  : ORIGIN = 0x0209a000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_78  : ORIGIN = 0x0209c000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_79  : ORIGIN = 0x0209e000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_80  : ORIGIN = 0x020a0000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_81  : ORIGIN = 0x020a2000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_82  : ORIGIN = 0x020a4000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_83  : ORIGIN = 0x020a6000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_84  : ORIGIN = 0x020a8000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_85  : ORIGIN = 0x020aa000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_86  : ORIGIN = 0x020ac000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_87  : ORIGIN = 0x020ae000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_88  : ORIGIN = 0x020b0000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_89  : ORIGIN = 0x020b2000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_90  : ORIGIN = 0x020b4000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_91  : ORIGIN = 0x020b6000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_92  : ORIGIN = 0x020b8000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_93  : ORIGIN = 0x020ba000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_94  : ORIGIN = 0x020bc000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_95  : ORIGIN = 0x020be000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_96  : ORIGIN = 0x020c0000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_97  : ORIGIN = 0x020c2000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_98  : ORIGIN = 0x020c4000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_99  : ORIGIN = 0x020c6000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_100 : ORIGIN = 0x020c8000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_101 : ORIGIN = 0x020ca000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_102 : ORIGIN = 0x020cc000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_103 : ORIGIN = 0x020ce000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_104 : ORIGIN = 0x020d0000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_105 : ORIGIN = 0x020d2000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_106 : ORIGIN = 0x020d4000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_107 : ORIGIN = 0x020d6000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_108 : ORIGIN = 0x020d8000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_109 : ORIGIN = 0x020da000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_110 : ORIGIN = 0x020dc000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_111 : ORIGIN = 0x020de000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_112 : ORIGIN = 0x020e0000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_113 : ORIGIN = 0x020e2000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_114 : ORIGIN = 0x020e4000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_115 : ORIGIN = 0x020e6000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_116 : ORIGIN = 0x020e8000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_117 : ORIGIN = 0x020ea000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_118 : ORIGIN = 0x020ec000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_119 : ORIGIN = 0x020ee000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_120 : ORIGIN = 0x020f0000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_121 : ORIGIN = 0x020f2000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_122 : ORIGIN = 0x020f4000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_123 : ORIGIN = 0x020f6000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_124 : ORIGIN = 0x020f8000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_125 : ORIGIN = 0x020fa000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_126 : ORIGIN = 0x020fc000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_127 : ORIGIN = 0x020fe000, LENGTH = __chr_rom_size >= 1024 ? 0x2000 : 0
  chr_rom_128 : ORIGIN = 0x02100000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_129 : ORIGIN = 0x02102000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_130 : ORIGIN = 0x02104000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_131 : ORIGIN = 0x02106000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_132 : ORIGIN = 0x02108000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_133 : ORIGIN = 0x0210a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_134 : ORIGIN = 0x0210c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_135 : ORIGIN = 0x0210e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_136 : ORIGIN = 0x02110000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_137 : ORIGIN = 0x02112000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_138 : ORIGIN = 0x02114000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_139 : ORIGIN = 0x02116000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_140 : ORIGIN = 0x02118000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_141 : ORIGIN = 0x0211a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_142 : ORIGIN = 0x0211c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_143 : ORIGIN = 0x0211e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_144 : ORIGIN = 0x02120000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_145 : ORIGIN = 0x02122000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_146 : ORIGIN = 0x02124000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_147 : ORIGIN = 0x02126000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_148 : ORIGIN = 0x02128000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_149 : ORIGIN = 0x0212a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_150 : ORIGIN = 0x0212c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_151 : ORIGIN = 0x0212e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_152 : ORIGIN = 0x02130000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_153 : ORIGIN = 0x02132000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_154 : ORIGIN = 0x02134000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_155 : ORIGIN = 0x02136000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_156 : ORIGIN = 0x02138000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_157 : ORIGIN = 0x0213a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_158 : ORIGIN = 0x0213c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_159 : ORIGIN = 0x0213e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_160 : ORIGIN = 0x02140000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_161 : ORIGIN = 0x02142000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_162 : ORIGIN = 0x02144000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_163 : ORIGIN = 0x02146000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_164 : ORIGIN = 0x02148000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_165 : ORIGIN = 0x0214a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_166 : ORIGIN = 0x0214c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_167 : ORIGIN = 0x0214e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_168 : ORIGIN = 0x02150000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_169 : ORIGIN = 0x02152000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_170 : ORIGIN = 0x02154000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_171 : ORIGIN = 0x02156000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_172 : ORIGIN = 0x02158000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_173 : ORIGIN = 0x0215a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_174 : ORIGIN = 0x0215c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_175 : ORIGIN = 0x0215e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_176 : ORIGIN = 0x02160000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_177 : ORIGIN = 0x02162000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_178 : ORIGIN = 0x02164000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_179 : ORIGIN = 0x02166000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_180 : ORIGIN = 0x02168000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_181 : ORIGIN = 0x0216a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_182 : ORIGIN = 0x0216c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_183 : ORIGIN = 0x0216e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_184 : ORIGIN = 0x02170000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_185 : ORIGIN = 0x02172000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_186 : ORIGIN = 0x02174000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_187 : ORIGIN = 0x02176000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_188 : ORIGIN = 0x02178000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_189 : ORIGIN = 0x0217a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_190 : ORIGIN = 0x0217c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_191 : ORIGIN = 0x0217e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_192 : ORIGIN = 0x02180000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_193 : ORIGIN = 0x02182000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_194 : ORIGIN = 0x02184000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_195 : ORIGIN = 0x02186000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_196 : ORIGIN = 0x02188000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_197 : ORIGIN = 0x0218a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_198 : ORIGIN = 0x0218c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_199 : ORIGIN = 0x0218e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_200 : ORIGIN = 0x02190000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_201 : ORIGIN = 0x02192000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_202 : ORIGIN = 0x02194000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_203 : ORIGIN = 0x02196000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_204 : ORIGIN = 0x02198000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_205 : ORIGIN = 0x0219a000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_206 : ORIGIN = 0x0219c000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_207 : ORIGIN = 0x0219e000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_208 : ORIGIN = 0x021a0000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_209 : ORIGIN = 0x021a2000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_210 : ORIGIN = 0x021a4000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_211 : ORIGIN = 0x021a6000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_212 : ORIGIN = 0x021a8000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_213 : ORIGIN = 0x021aa000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_214 : ORIGIN = 0x021ac000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_215 : ORIGIN = 0x021ae000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_216 : ORIGIN = 0x021b0000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_217 : ORIGIN = 0x021b2000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_218 : ORIGIN = 0x021b4000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_219 : ORIGIN = 0x021b6000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_220 : ORIGIN = 0x021b8000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_221 : ORIGIN = 0x021ba000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_222 : ORIGIN = 0x021bc000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_223 : ORIGIN = 0x021be000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_224 : ORIGIN = 0x021c0000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_225 : ORIGIN = 0x021c2000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_226 : ORIGIN = 0x021c4000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_227 : ORIGIN = 0x021c6000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_228 : ORIGIN = 0x021c8000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_229 : ORIGIN = 0x021ca000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_230 : ORIGIN = 0x021cc000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_231 : ORIGIN = 0x021ce000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_232 : ORIGIN = 0x021d0000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_233 : ORIGIN = 0x021d2000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_234 : ORIGIN = 0x021d4000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_235 : ORIGIN = 0x021d6000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_236 : ORIGIN = 0x021d8000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_237 : ORIGIN = 0x021da000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_238 : ORIGIN = 0x021dc000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_239 : ORIGIN = 0x021de000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_240 : ORIGIN = 0x021e0000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_241 : ORIGIN = 0x021e2000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_242 : ORIGIN = 0x021e4000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_243 : ORIGIN = 0x021e6000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_244 : ORIGIN = 0x021e8000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_245 : ORIGIN = 0x021ea000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_246 : ORIGIN = 0x021ec000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_247 : ORIGIN = 0x021ee000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_248 : ORIGIN = 0x021f0000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_249 : ORIGIN = 0x021f2000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_250 : ORIGIN = 0x021f4000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_251 : ORIGIN = 0x021f6000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_252 : ORIGIN = 0x021f8000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_253 : ORIGIN = 0x021fa000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_254 : ORIGIN = 0x021fc000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
  chr_rom_255 : ORIGIN = 0x021fe000, LENGTH = __chr_rom_size >= 2048 ? 0x2000 : 0
}

SECTIONS {
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
}

INCLUDE ines.ld
