PROVIDE(__prg_rom_0 = 0x8000);
PROVIDE(__prg_rom_1 = 0xa000);
PROVIDE(__prg_rom_2 = 0x8000);
PROVIDE(__prg_rom_3 = 0xa000);
PROVIDE(__prg_rom_4 = 0x8000);
PROVIDE(__prg_rom_5 = 0xa000);
PROVIDE(__prg_rom_6 = 0x8000);
PROVIDE(__prg_rom_7 = 0xa000);
PROVIDE(__prg_rom_8 = 0x8000);
PROVIDE(__prg_rom_9 = 0xa000);
PROVIDE(__prg_rom_10 = 0x8000);
PROVIDE(__prg_rom_11 = 0xa000);
PROVIDE(__prg_rom_12 = 0x8000);
PROVIDE(__prg_rom_13 = 0xa000);
PROVIDE(__prg_rom_14 = 0x8000);
PROVIDE(__prg_rom_15 = 0xa000);
PROVIDE(__prg_rom_16 = 0x8000);
PROVIDE(__prg_rom_17 = 0xa000);
PROVIDE(__prg_rom_18 = 0x8000);
PROVIDE(__prg_rom_19 = 0xa000);
PROVIDE(__prg_rom_20 = 0x8000);
PROVIDE(__prg_rom_21 = 0xa000);
PROVIDE(__prg_rom_22 = 0x8000);
PROVIDE(__prg_rom_23 = 0xa000);
PROVIDE(__prg_rom_24 = 0x8000);
PROVIDE(__prg_rom_25 = 0xa000);
PROVIDE(__prg_rom_26 = 0x8000);
PROVIDE(__prg_rom_27 = 0xa000);
PROVIDE(__prg_rom_28 = 0x8000);
PROVIDE(__prg_rom_29 = 0xa000);
PROVIDE(__prg_rom_30 = 0x8000);
PROVIDE(__prg_rom_31 = 0xa000);
PROVIDE(__prg_rom_32 = 0x8000);
PROVIDE(__prg_rom_33 = 0xa000);
PROVIDE(__prg_rom_34 = 0x8000);
PROVIDE(__prg_rom_35 = 0xa000);
PROVIDE(__prg_rom_36 = 0x8000);
PROVIDE(__prg_rom_37 = 0xa000);
PROVIDE(__prg_rom_38 = 0x8000);
PROVIDE(__prg_rom_39 = 0xa000);
PROVIDE(__prg_rom_40 = 0x8000);
PROVIDE(__prg_rom_41 = 0xa000);
PROVIDE(__prg_rom_42 = 0x8000);
PROVIDE(__prg_rom_43 = 0xa000);
PROVIDE(__prg_rom_44 = 0x8000);
PROVIDE(__prg_rom_45 = 0xa000);
PROVIDE(__prg_rom_46 = 0x8000);
PROVIDE(__prg_rom_47 = 0xa000);
PROVIDE(__prg_rom_48 = 0x8000);
PROVIDE(__prg_rom_49 = 0xa000);
PROVIDE(__prg_rom_50 = 0x8000);
PROVIDE(__prg_rom_51 = 0xa000);
PROVIDE(__prg_rom_52 = 0x8000);
PROVIDE(__prg_rom_53 = 0xa000);
PROVIDE(__prg_rom_54 = 0x8000);
PROVIDE(__prg_rom_55 = 0xa000);
PROVIDE(__prg_rom_56 = 0x8000);
PROVIDE(__prg_rom_57 = 0xa000);
PROVIDE(__prg_rom_58 = 0x8000);
PROVIDE(__prg_rom_59 = 0xa000);
PROVIDE(__prg_rom_60 = 0x8000);

INCLUDE _prg-rom-banked.ld

INPUT(reset-banked-mode-0.o)

__prg_rom_61_lma    = 0x3da000;
__prg_rom_fixed_lma = 0x00c000;

__prg_rom_61_offset    = 0x7a000;
__prg_rom_fixed_offset = __prg_rom_size * 1024 - 0x4000;

MEMORY {
  prg_rom_61    : ORIGIN = __prg_rom_61_lma,    LENGTH = __prg_rom_size == 512 ? 0x2000 : 0
  prg_rom_fixed : ORIGIN = __prg_rom_fixed_lma, LENGTH = 0x4000
}
REGION_ALIAS("c_rom", prg_rom_fixed)

SECTIONS { .prg_rom_61 : { *(.prg_rom_61 .prg_rom_61.*) } >prg_rom_61 }

INCLUDE dpcm.ld
INCLUDE _reset.ld

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)
  FULL(prg_rom_1)
  FULL(prg_rom_2)
  FULL(prg_rom_3)
  FULL(prg_rom_4)
  FULL(prg_rom_5)
  FULL(prg_rom_6)
  FULL(prg_rom_7)
  FULL(prg_rom_8)
  FULL(prg_rom_9)
  FULL(prg_rom_10)
  FULL(prg_rom_11)
  FULL(prg_rom_12)
  FULL(prg_rom_13)
  FULL(prg_rom_14)
  FULL(prg_rom_15)
  FULL(prg_rom_16)
  FULL(prg_rom_17)
  FULL(prg_rom_18)
  FULL(prg_rom_19)
  FULL(prg_rom_20)
  FULL(prg_rom_21)
  FULL(prg_rom_22)
  FULL(prg_rom_23)
  FULL(prg_rom_24)
  FULL(prg_rom_25)
  FULL(prg_rom_26)
  FULL(prg_rom_27)
  FULL(prg_rom_28)
  FULL(prg_rom_29)
  FULL(prg_rom_30)
  FULL(prg_rom_31)
  FULL(prg_rom_32)
  FULL(prg_rom_33)
  FULL(prg_rom_34)
  FULL(prg_rom_35)
  FULL(prg_rom_36)
  FULL(prg_rom_37)
  FULL(prg_rom_38)
  FULL(prg_rom_39)
  FULL(prg_rom_40)
  FULL(prg_rom_41)
  FULL(prg_rom_42)
  FULL(prg_rom_43)
  FULL(prg_rom_44)
  FULL(prg_rom_45)
  FULL(prg_rom_46)
  FULL(prg_rom_47)
  FULL(prg_rom_48)
  FULL(prg_rom_49)
  FULL(prg_rom_50)
  FULL(prg_rom_51)
  FULL(prg_rom_52)
  FULL(prg_rom_53)
  FULL(prg_rom_54)
  FULL(prg_rom_55)
  FULL(prg_rom_56)
  FULL(prg_rom_57)
  FULL(prg_rom_58)
  FULL(prg_rom_59)
  FULL(prg_rom_60)
  FULL(prg_rom_61)
  FULL(prg_rom_fixed)
  FULL(chr_rom)
}
