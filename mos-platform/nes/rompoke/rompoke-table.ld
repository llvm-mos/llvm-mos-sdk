/**
 * Automatically generated by generate-rompoke-table-linkscript.lua.
 *
 * This script generates a ROM poke table (nes/misc/rompoke/README.md) with
 * a dynamic size determined by the symbol __rom_poke_table_size.
 *
 * Each section defines one byte of the table, from .rom_poke_table_0
 * to .rom_poke_table_255. Each section is filled in its totality with the
 * respective value 0 to 255; however, "totality" means either one byte
 * (for sections N <= __rom_poke_table_size) or zero bytes, omitting the value
 * (for sections N > __rom_poke_table_size). This has the effect of only
 * emitting a byte in "__rom_poke_table_size" consecutive sections, creating
 * the desired dynamically sized table.
 *
 * The fill pattern chooses to emit all four bytes as a repeating sequence,
 * as the value is interpreted as big-endian, even though we only use one byte
 * of that.
 */
SECTIONS {
  .rom_poke_table_0 : {
    __rom_poke_table = .;
    FILL(0x00000000)
    . = . + (__rom_poke_table_size > 0 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_1 : {
    FILL(0x01010101)
    . = . + (__rom_poke_table_size > 1 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_2 : {
    FILL(0x02020202)
    . = . + (__rom_poke_table_size > 2 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_3 : {
    FILL(0x03030303)
    . = . + (__rom_poke_table_size > 3 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_4 : {
    FILL(0x04040404)
    . = . + (__rom_poke_table_size > 4 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_5 : {
    FILL(0x05050505)
    . = . + (__rom_poke_table_size > 5 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_6 : {
    FILL(0x06060606)
    . = . + (__rom_poke_table_size > 6 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_7 : {
    FILL(0x07070707)
    . = . + (__rom_poke_table_size > 7 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_8 : {
    FILL(0x08080808)
    . = . + (__rom_poke_table_size > 8 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_9 : {
    FILL(0x09090909)
    . = . + (__rom_poke_table_size > 9 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_10 : {
    FILL(0x0A0A0A0A)
    . = . + (__rom_poke_table_size > 10 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_11 : {
    FILL(0x0B0B0B0B)
    . = . + (__rom_poke_table_size > 11 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_12 : {
    FILL(0x0C0C0C0C)
    . = . + (__rom_poke_table_size > 12 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_13 : {
    FILL(0x0D0D0D0D)
    . = . + (__rom_poke_table_size > 13 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_14 : {
    FILL(0x0E0E0E0E)
    . = . + (__rom_poke_table_size > 14 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_15 : {
    FILL(0x0F0F0F0F)
    . = . + (__rom_poke_table_size > 15 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_16 : {
    FILL(0x10101010)
    . = . + (__rom_poke_table_size > 16 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_17 : {
    FILL(0x11111111)
    . = . + (__rom_poke_table_size > 17 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_18 : {
    FILL(0x12121212)
    . = . + (__rom_poke_table_size > 18 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_19 : {
    FILL(0x13131313)
    . = . + (__rom_poke_table_size > 19 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_20 : {
    FILL(0x14141414)
    . = . + (__rom_poke_table_size > 20 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_21 : {
    FILL(0x15151515)
    . = . + (__rom_poke_table_size > 21 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_22 : {
    FILL(0x16161616)
    . = . + (__rom_poke_table_size > 22 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_23 : {
    FILL(0x17171717)
    . = . + (__rom_poke_table_size > 23 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_24 : {
    FILL(0x18181818)
    . = . + (__rom_poke_table_size > 24 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_25 : {
    FILL(0x19191919)
    . = . + (__rom_poke_table_size > 25 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_26 : {
    FILL(0x1A1A1A1A)
    . = . + (__rom_poke_table_size > 26 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_27 : {
    FILL(0x1B1B1B1B)
    . = . + (__rom_poke_table_size > 27 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_28 : {
    FILL(0x1C1C1C1C)
    . = . + (__rom_poke_table_size > 28 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_29 : {
    FILL(0x1D1D1D1D)
    . = . + (__rom_poke_table_size > 29 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_30 : {
    FILL(0x1E1E1E1E)
    . = . + (__rom_poke_table_size > 30 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_31 : {
    FILL(0x1F1F1F1F)
    . = . + (__rom_poke_table_size > 31 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_32 : {
    FILL(0x20202020)
    . = . + (__rom_poke_table_size > 32 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_33 : {
    FILL(0x21212121)
    . = . + (__rom_poke_table_size > 33 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_34 : {
    FILL(0x22222222)
    . = . + (__rom_poke_table_size > 34 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_35 : {
    FILL(0x23232323)
    . = . + (__rom_poke_table_size > 35 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_36 : {
    FILL(0x24242424)
    . = . + (__rom_poke_table_size > 36 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_37 : {
    FILL(0x25252525)
    . = . + (__rom_poke_table_size > 37 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_38 : {
    FILL(0x26262626)
    . = . + (__rom_poke_table_size > 38 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_39 : {
    FILL(0x27272727)
    . = . + (__rom_poke_table_size > 39 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_40 : {
    FILL(0x28282828)
    . = . + (__rom_poke_table_size > 40 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_41 : {
    FILL(0x29292929)
    . = . + (__rom_poke_table_size > 41 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_42 : {
    FILL(0x2A2A2A2A)
    . = . + (__rom_poke_table_size > 42 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_43 : {
    FILL(0x2B2B2B2B)
    . = . + (__rom_poke_table_size > 43 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_44 : {
    FILL(0x2C2C2C2C)
    . = . + (__rom_poke_table_size > 44 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_45 : {
    FILL(0x2D2D2D2D)
    . = . + (__rom_poke_table_size > 45 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_46 : {
    FILL(0x2E2E2E2E)
    . = . + (__rom_poke_table_size > 46 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_47 : {
    FILL(0x2F2F2F2F)
    . = . + (__rom_poke_table_size > 47 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_48 : {
    FILL(0x30303030)
    . = . + (__rom_poke_table_size > 48 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_49 : {
    FILL(0x31313131)
    . = . + (__rom_poke_table_size > 49 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_50 : {
    FILL(0x32323232)
    . = . + (__rom_poke_table_size > 50 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_51 : {
    FILL(0x33333333)
    . = . + (__rom_poke_table_size > 51 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_52 : {
    FILL(0x34343434)
    . = . + (__rom_poke_table_size > 52 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_53 : {
    FILL(0x35353535)
    . = . + (__rom_poke_table_size > 53 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_54 : {
    FILL(0x36363636)
    . = . + (__rom_poke_table_size > 54 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_55 : {
    FILL(0x37373737)
    . = . + (__rom_poke_table_size > 55 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_56 : {
    FILL(0x38383838)
    . = . + (__rom_poke_table_size > 56 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_57 : {
    FILL(0x39393939)
    . = . + (__rom_poke_table_size > 57 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_58 : {
    FILL(0x3A3A3A3A)
    . = . + (__rom_poke_table_size > 58 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_59 : {
    FILL(0x3B3B3B3B)
    . = . + (__rom_poke_table_size > 59 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_60 : {
    FILL(0x3C3C3C3C)
    . = . + (__rom_poke_table_size > 60 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_61 : {
    FILL(0x3D3D3D3D)
    . = . + (__rom_poke_table_size > 61 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_62 : {
    FILL(0x3E3E3E3E)
    . = . + (__rom_poke_table_size > 62 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_63 : {
    FILL(0x3F3F3F3F)
    . = . + (__rom_poke_table_size > 63 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_64 : {
    FILL(0x40404040)
    . = . + (__rom_poke_table_size > 64 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_65 : {
    FILL(0x41414141)
    . = . + (__rom_poke_table_size > 65 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_66 : {
    FILL(0x42424242)
    . = . + (__rom_poke_table_size > 66 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_67 : {
    FILL(0x43434343)
    . = . + (__rom_poke_table_size > 67 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_68 : {
    FILL(0x44444444)
    . = . + (__rom_poke_table_size > 68 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_69 : {
    FILL(0x45454545)
    . = . + (__rom_poke_table_size > 69 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_70 : {
    FILL(0x46464646)
    . = . + (__rom_poke_table_size > 70 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_71 : {
    FILL(0x47474747)
    . = . + (__rom_poke_table_size > 71 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_72 : {
    FILL(0x48484848)
    . = . + (__rom_poke_table_size > 72 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_73 : {
    FILL(0x49494949)
    . = . + (__rom_poke_table_size > 73 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_74 : {
    FILL(0x4A4A4A4A)
    . = . + (__rom_poke_table_size > 74 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_75 : {
    FILL(0x4B4B4B4B)
    . = . + (__rom_poke_table_size > 75 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_76 : {
    FILL(0x4C4C4C4C)
    . = . + (__rom_poke_table_size > 76 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_77 : {
    FILL(0x4D4D4D4D)
    . = . + (__rom_poke_table_size > 77 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_78 : {
    FILL(0x4E4E4E4E)
    . = . + (__rom_poke_table_size > 78 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_79 : {
    FILL(0x4F4F4F4F)
    . = . + (__rom_poke_table_size > 79 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_80 : {
    FILL(0x50505050)
    . = . + (__rom_poke_table_size > 80 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_81 : {
    FILL(0x51515151)
    . = . + (__rom_poke_table_size > 81 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_82 : {
    FILL(0x52525252)
    . = . + (__rom_poke_table_size > 82 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_83 : {
    FILL(0x53535353)
    . = . + (__rom_poke_table_size > 83 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_84 : {
    FILL(0x54545454)
    . = . + (__rom_poke_table_size > 84 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_85 : {
    FILL(0x55555555)
    . = . + (__rom_poke_table_size > 85 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_86 : {
    FILL(0x56565656)
    . = . + (__rom_poke_table_size > 86 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_87 : {
    FILL(0x57575757)
    . = . + (__rom_poke_table_size > 87 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_88 : {
    FILL(0x58585858)
    . = . + (__rom_poke_table_size > 88 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_89 : {
    FILL(0x59595959)
    . = . + (__rom_poke_table_size > 89 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_90 : {
    FILL(0x5A5A5A5A)
    . = . + (__rom_poke_table_size > 90 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_91 : {
    FILL(0x5B5B5B5B)
    . = . + (__rom_poke_table_size > 91 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_92 : {
    FILL(0x5C5C5C5C)
    . = . + (__rom_poke_table_size > 92 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_93 : {
    FILL(0x5D5D5D5D)
    . = . + (__rom_poke_table_size > 93 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_94 : {
    FILL(0x5E5E5E5E)
    . = . + (__rom_poke_table_size > 94 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_95 : {
    FILL(0x5F5F5F5F)
    . = . + (__rom_poke_table_size > 95 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_96 : {
    FILL(0x60606060)
    . = . + (__rom_poke_table_size > 96 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_97 : {
    FILL(0x61616161)
    . = . + (__rom_poke_table_size > 97 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_98 : {
    FILL(0x62626262)
    . = . + (__rom_poke_table_size > 98 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_99 : {
    FILL(0x63636363)
    . = . + (__rom_poke_table_size > 99 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_100 : {
    FILL(0x64646464)
    . = . + (__rom_poke_table_size > 100 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_101 : {
    FILL(0x65656565)
    . = . + (__rom_poke_table_size > 101 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_102 : {
    FILL(0x66666666)
    . = . + (__rom_poke_table_size > 102 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_103 : {
    FILL(0x67676767)
    . = . + (__rom_poke_table_size > 103 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_104 : {
    FILL(0x68686868)
    . = . + (__rom_poke_table_size > 104 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_105 : {
    FILL(0x69696969)
    . = . + (__rom_poke_table_size > 105 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_106 : {
    FILL(0x6A6A6A6A)
    . = . + (__rom_poke_table_size > 106 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_107 : {
    FILL(0x6B6B6B6B)
    . = . + (__rom_poke_table_size > 107 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_108 : {
    FILL(0x6C6C6C6C)
    . = . + (__rom_poke_table_size > 108 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_109 : {
    FILL(0x6D6D6D6D)
    . = . + (__rom_poke_table_size > 109 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_110 : {
    FILL(0x6E6E6E6E)
    . = . + (__rom_poke_table_size > 110 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_111 : {
    FILL(0x6F6F6F6F)
    . = . + (__rom_poke_table_size > 111 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_112 : {
    FILL(0x70707070)
    . = . + (__rom_poke_table_size > 112 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_113 : {
    FILL(0x71717171)
    . = . + (__rom_poke_table_size > 113 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_114 : {
    FILL(0x72727272)
    . = . + (__rom_poke_table_size > 114 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_115 : {
    FILL(0x73737373)
    . = . + (__rom_poke_table_size > 115 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_116 : {
    FILL(0x74747474)
    . = . + (__rom_poke_table_size > 116 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_117 : {
    FILL(0x75757575)
    . = . + (__rom_poke_table_size > 117 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_118 : {
    FILL(0x76767676)
    . = . + (__rom_poke_table_size > 118 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_119 : {
    FILL(0x77777777)
    . = . + (__rom_poke_table_size > 119 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_120 : {
    FILL(0x78787878)
    . = . + (__rom_poke_table_size > 120 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_121 : {
    FILL(0x79797979)
    . = . + (__rom_poke_table_size > 121 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_122 : {
    FILL(0x7A7A7A7A)
    . = . + (__rom_poke_table_size > 122 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_123 : {
    FILL(0x7B7B7B7B)
    . = . + (__rom_poke_table_size > 123 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_124 : {
    FILL(0x7C7C7C7C)
    . = . + (__rom_poke_table_size > 124 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_125 : {
    FILL(0x7D7D7D7D)
    . = . + (__rom_poke_table_size > 125 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_126 : {
    FILL(0x7E7E7E7E)
    . = . + (__rom_poke_table_size > 126 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_127 : {
    FILL(0x7F7F7F7F)
    . = . + (__rom_poke_table_size > 127 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_128 : {
    FILL(0x80808080)
    . = . + (__rom_poke_table_size > 128 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_129 : {
    FILL(0x81818181)
    . = . + (__rom_poke_table_size > 129 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_130 : {
    FILL(0x82828282)
    . = . + (__rom_poke_table_size > 130 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_131 : {
    FILL(0x83838383)
    . = . + (__rom_poke_table_size > 131 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_132 : {
    FILL(0x84848484)
    . = . + (__rom_poke_table_size > 132 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_133 : {
    FILL(0x85858585)
    . = . + (__rom_poke_table_size > 133 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_134 : {
    FILL(0x86868686)
    . = . + (__rom_poke_table_size > 134 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_135 : {
    FILL(0x87878787)
    . = . + (__rom_poke_table_size > 135 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_136 : {
    FILL(0x88888888)
    . = . + (__rom_poke_table_size > 136 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_137 : {
    FILL(0x89898989)
    . = . + (__rom_poke_table_size > 137 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_138 : {
    FILL(0x8A8A8A8A)
    . = . + (__rom_poke_table_size > 138 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_139 : {
    FILL(0x8B8B8B8B)
    . = . + (__rom_poke_table_size > 139 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_140 : {
    FILL(0x8C8C8C8C)
    . = . + (__rom_poke_table_size > 140 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_141 : {
    FILL(0x8D8D8D8D)
    . = . + (__rom_poke_table_size > 141 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_142 : {
    FILL(0x8E8E8E8E)
    . = . + (__rom_poke_table_size > 142 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_143 : {
    FILL(0x8F8F8F8F)
    . = . + (__rom_poke_table_size > 143 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_144 : {
    FILL(0x90909090)
    . = . + (__rom_poke_table_size > 144 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_145 : {
    FILL(0x91919191)
    . = . + (__rom_poke_table_size > 145 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_146 : {
    FILL(0x92929292)
    . = . + (__rom_poke_table_size > 146 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_147 : {
    FILL(0x93939393)
    . = . + (__rom_poke_table_size > 147 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_148 : {
    FILL(0x94949494)
    . = . + (__rom_poke_table_size > 148 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_149 : {
    FILL(0x95959595)
    . = . + (__rom_poke_table_size > 149 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_150 : {
    FILL(0x96969696)
    . = . + (__rom_poke_table_size > 150 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_151 : {
    FILL(0x97979797)
    . = . + (__rom_poke_table_size > 151 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_152 : {
    FILL(0x98989898)
    . = . + (__rom_poke_table_size > 152 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_153 : {
    FILL(0x99999999)
    . = . + (__rom_poke_table_size > 153 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_154 : {
    FILL(0x9A9A9A9A)
    . = . + (__rom_poke_table_size > 154 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_155 : {
    FILL(0x9B9B9B9B)
    . = . + (__rom_poke_table_size > 155 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_156 : {
    FILL(0x9C9C9C9C)
    . = . + (__rom_poke_table_size > 156 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_157 : {
    FILL(0x9D9D9D9D)
    . = . + (__rom_poke_table_size > 157 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_158 : {
    FILL(0x9E9E9E9E)
    . = . + (__rom_poke_table_size > 158 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_159 : {
    FILL(0x9F9F9F9F)
    . = . + (__rom_poke_table_size > 159 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_160 : {
    FILL(0xA0A0A0A0)
    . = . + (__rom_poke_table_size > 160 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_161 : {
    FILL(0xA1A1A1A1)
    . = . + (__rom_poke_table_size > 161 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_162 : {
    FILL(0xA2A2A2A2)
    . = . + (__rom_poke_table_size > 162 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_163 : {
    FILL(0xA3A3A3A3)
    . = . + (__rom_poke_table_size > 163 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_164 : {
    FILL(0xA4A4A4A4)
    . = . + (__rom_poke_table_size > 164 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_165 : {
    FILL(0xA5A5A5A5)
    . = . + (__rom_poke_table_size > 165 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_166 : {
    FILL(0xA6A6A6A6)
    . = . + (__rom_poke_table_size > 166 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_167 : {
    FILL(0xA7A7A7A7)
    . = . + (__rom_poke_table_size > 167 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_168 : {
    FILL(0xA8A8A8A8)
    . = . + (__rom_poke_table_size > 168 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_169 : {
    FILL(0xA9A9A9A9)
    . = . + (__rom_poke_table_size > 169 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_170 : {
    FILL(0xAAAAAAAA)
    . = . + (__rom_poke_table_size > 170 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_171 : {
    FILL(0xABABABAB)
    . = . + (__rom_poke_table_size > 171 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_172 : {
    FILL(0xACACACAC)
    . = . + (__rom_poke_table_size > 172 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_173 : {
    FILL(0xADADADAD)
    . = . + (__rom_poke_table_size > 173 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_174 : {
    FILL(0xAEAEAEAE)
    . = . + (__rom_poke_table_size > 174 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_175 : {
    FILL(0xAFAFAFAF)
    . = . + (__rom_poke_table_size > 175 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_176 : {
    FILL(0xB0B0B0B0)
    . = . + (__rom_poke_table_size > 176 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_177 : {
    FILL(0xB1B1B1B1)
    . = . + (__rom_poke_table_size > 177 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_178 : {
    FILL(0xB2B2B2B2)
    . = . + (__rom_poke_table_size > 178 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_179 : {
    FILL(0xB3B3B3B3)
    . = . + (__rom_poke_table_size > 179 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_180 : {
    FILL(0xB4B4B4B4)
    . = . + (__rom_poke_table_size > 180 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_181 : {
    FILL(0xB5B5B5B5)
    . = . + (__rom_poke_table_size > 181 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_182 : {
    FILL(0xB6B6B6B6)
    . = . + (__rom_poke_table_size > 182 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_183 : {
    FILL(0xB7B7B7B7)
    . = . + (__rom_poke_table_size > 183 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_184 : {
    FILL(0xB8B8B8B8)
    . = . + (__rom_poke_table_size > 184 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_185 : {
    FILL(0xB9B9B9B9)
    . = . + (__rom_poke_table_size > 185 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_186 : {
    FILL(0xBABABABA)
    . = . + (__rom_poke_table_size > 186 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_187 : {
    FILL(0xBBBBBBBB)
    . = . + (__rom_poke_table_size > 187 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_188 : {
    FILL(0xBCBCBCBC)
    . = . + (__rom_poke_table_size > 188 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_189 : {
    FILL(0xBDBDBDBD)
    . = . + (__rom_poke_table_size > 189 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_190 : {
    FILL(0xBEBEBEBE)
    . = . + (__rom_poke_table_size > 190 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_191 : {
    FILL(0xBFBFBFBF)
    . = . + (__rom_poke_table_size > 191 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_192 : {
    FILL(0xC0C0C0C0)
    . = . + (__rom_poke_table_size > 192 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_193 : {
    FILL(0xC1C1C1C1)
    . = . + (__rom_poke_table_size > 193 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_194 : {
    FILL(0xC2C2C2C2)
    . = . + (__rom_poke_table_size > 194 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_195 : {
    FILL(0xC3C3C3C3)
    . = . + (__rom_poke_table_size > 195 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_196 : {
    FILL(0xC4C4C4C4)
    . = . + (__rom_poke_table_size > 196 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_197 : {
    FILL(0xC5C5C5C5)
    . = . + (__rom_poke_table_size > 197 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_198 : {
    FILL(0xC6C6C6C6)
    . = . + (__rom_poke_table_size > 198 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_199 : {
    FILL(0xC7C7C7C7)
    . = . + (__rom_poke_table_size > 199 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_200 : {
    FILL(0xC8C8C8C8)
    . = . + (__rom_poke_table_size > 200 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_201 : {
    FILL(0xC9C9C9C9)
    . = . + (__rom_poke_table_size > 201 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_202 : {
    FILL(0xCACACACA)
    . = . + (__rom_poke_table_size > 202 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_203 : {
    FILL(0xCBCBCBCB)
    . = . + (__rom_poke_table_size > 203 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_204 : {
    FILL(0xCCCCCCCC)
    . = . + (__rom_poke_table_size > 204 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_205 : {
    FILL(0xCDCDCDCD)
    . = . + (__rom_poke_table_size > 205 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_206 : {
    FILL(0xCECECECE)
    . = . + (__rom_poke_table_size > 206 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_207 : {
    FILL(0xCFCFCFCF)
    . = . + (__rom_poke_table_size > 207 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_208 : {
    FILL(0xD0D0D0D0)
    . = . + (__rom_poke_table_size > 208 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_209 : {
    FILL(0xD1D1D1D1)
    . = . + (__rom_poke_table_size > 209 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_210 : {
    FILL(0xD2D2D2D2)
    . = . + (__rom_poke_table_size > 210 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_211 : {
    FILL(0xD3D3D3D3)
    . = . + (__rom_poke_table_size > 211 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_212 : {
    FILL(0xD4D4D4D4)
    . = . + (__rom_poke_table_size > 212 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_213 : {
    FILL(0xD5D5D5D5)
    . = . + (__rom_poke_table_size > 213 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_214 : {
    FILL(0xD6D6D6D6)
    . = . + (__rom_poke_table_size > 214 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_215 : {
    FILL(0xD7D7D7D7)
    . = . + (__rom_poke_table_size > 215 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_216 : {
    FILL(0xD8D8D8D8)
    . = . + (__rom_poke_table_size > 216 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_217 : {
    FILL(0xD9D9D9D9)
    . = . + (__rom_poke_table_size > 217 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_218 : {
    FILL(0xDADADADA)
    . = . + (__rom_poke_table_size > 218 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_219 : {
    FILL(0xDBDBDBDB)
    . = . + (__rom_poke_table_size > 219 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_220 : {
    FILL(0xDCDCDCDC)
    . = . + (__rom_poke_table_size > 220 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_221 : {
    FILL(0xDDDDDDDD)
    . = . + (__rom_poke_table_size > 221 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_222 : {
    FILL(0xDEDEDEDE)
    . = . + (__rom_poke_table_size > 222 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_223 : {
    FILL(0xDFDFDFDF)
    . = . + (__rom_poke_table_size > 223 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_224 : {
    FILL(0xE0E0E0E0)
    . = . + (__rom_poke_table_size > 224 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_225 : {
    FILL(0xE1E1E1E1)
    . = . + (__rom_poke_table_size > 225 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_226 : {
    FILL(0xE2E2E2E2)
    . = . + (__rom_poke_table_size > 226 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_227 : {
    FILL(0xE3E3E3E3)
    . = . + (__rom_poke_table_size > 227 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_228 : {
    FILL(0xE4E4E4E4)
    . = . + (__rom_poke_table_size > 228 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_229 : {
    FILL(0xE5E5E5E5)
    . = . + (__rom_poke_table_size > 229 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_230 : {
    FILL(0xE6E6E6E6)
    . = . + (__rom_poke_table_size > 230 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_231 : {
    FILL(0xE7E7E7E7)
    . = . + (__rom_poke_table_size > 231 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_232 : {
    FILL(0xE8E8E8E8)
    . = . + (__rom_poke_table_size > 232 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_233 : {
    FILL(0xE9E9E9E9)
    . = . + (__rom_poke_table_size > 233 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_234 : {
    FILL(0xEAEAEAEA)
    . = . + (__rom_poke_table_size > 234 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_235 : {
    FILL(0xEBEBEBEB)
    . = . + (__rom_poke_table_size > 235 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_236 : {
    FILL(0xECECECEC)
    . = . + (__rom_poke_table_size > 236 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_237 : {
    FILL(0xEDEDEDED)
    . = . + (__rom_poke_table_size > 237 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_238 : {
    FILL(0xEEEEEEEE)
    . = . + (__rom_poke_table_size > 238 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_239 : {
    FILL(0xEFEFEFEF)
    . = . + (__rom_poke_table_size > 239 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_240 : {
    FILL(0xF0F0F0F0)
    . = . + (__rom_poke_table_size > 240 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_241 : {
    FILL(0xF1F1F1F1)
    . = . + (__rom_poke_table_size > 241 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_242 : {
    FILL(0xF2F2F2F2)
    . = . + (__rom_poke_table_size > 242 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_243 : {
    FILL(0xF3F3F3F3)
    . = . + (__rom_poke_table_size > 243 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_244 : {
    FILL(0xF4F4F4F4)
    . = . + (__rom_poke_table_size > 244 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_245 : {
    FILL(0xF5F5F5F5)
    . = . + (__rom_poke_table_size > 245 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_246 : {
    FILL(0xF6F6F6F6)
    . = . + (__rom_poke_table_size > 246 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_247 : {
    FILL(0xF7F7F7F7)
    . = . + (__rom_poke_table_size > 247 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_248 : {
    FILL(0xF8F8F8F8)
    . = . + (__rom_poke_table_size > 248 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_249 : {
    FILL(0xF9F9F9F9)
    . = . + (__rom_poke_table_size > 249 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_250 : {
    FILL(0xFAFAFAFA)
    . = . + (__rom_poke_table_size > 250 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_251 : {
    FILL(0xFBFBFBFB)
    . = . + (__rom_poke_table_size > 251 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_252 : {
    FILL(0xFCFCFCFC)
    . = . + (__rom_poke_table_size > 252 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_253 : {
    FILL(0xFDFDFDFD)
    . = . + (__rom_poke_table_size > 253 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_254 : {
    FILL(0xFEFEFEFE)
    . = . + (__rom_poke_table_size > 254 ? 1 : 0);
  } >c_readonly
  .rom_poke_table_255 : {
    FILL(0xFFFFFFFF)
    . = . + (__rom_poke_table_size > 255 ? 1 : 0);
  } >c_readonly
}
