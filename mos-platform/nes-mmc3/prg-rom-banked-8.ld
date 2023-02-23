PROVIDE(__prg_rom_0  = 0x8000);
PROVIDE(__prg_rom_1  = 0x8000);
PROVIDE(__prg_rom_2  = 0x8000);
PROVIDE(__prg_rom_3  = 0x8000);
PROVIDE(__prg_rom_4  = 0x8000);
PROVIDE(__prg_rom_5  = 0x8000);
PROVIDE(__prg_rom_6  = 0x8000);
PROVIDE(__prg_rom_7  = 0x8000);
PROVIDE(__prg_rom_8  = 0x8000);
PROVIDE(__prg_rom_9  = 0x8000);
PROVIDE(__prg_rom_10 = 0x8000);
PROVIDE(__prg_rom_11 = 0x8000);
PROVIDE(__prg_rom_12 = 0x8000);
PROVIDE(__prg_rom_13 = 0x8000);
PROVIDE(__prg_rom_14 = 0x8000);
PROVIDE(__prg_rom_15 = 0x8000);
PROVIDE(__prg_rom_16 = 0x8000);
PROVIDE(__prg_rom_17 = 0x8000);
PROVIDE(__prg_rom_18 = 0x8000);
PROVIDE(__prg_rom_19 = 0x8000);
PROVIDE(__prg_rom_20 = 0x8000);
PROVIDE(__prg_rom_21 = 0x8000);
PROVIDE(__prg_rom_22 = 0x8000);
PROVIDE(__prg_rom_23 = 0x8000);
PROVIDE(__prg_rom_24 = 0x8000);
PROVIDE(__prg_rom_25 = 0x8000);
PROVIDE(__prg_rom_26 = 0x8000);
PROVIDE(__prg_rom_27 = 0x8000);
PROVIDE(__prg_rom_28 = 0x8000);
PROVIDE(__prg_rom_29 = 0x8000);
PROVIDE(__prg_rom_30 = 0x8000);
PROVIDE(__prg_rom_31 = 0x8000);
PROVIDE(__prg_rom_32 = 0x8000);
PROVIDE(__prg_rom_33 = 0x8000);
PROVIDE(__prg_rom_34 = 0x8000);
PROVIDE(__prg_rom_35 = 0x8000);
PROVIDE(__prg_rom_36 = 0x8000);
PROVIDE(__prg_rom_37 = 0x8000);
PROVIDE(__prg_rom_38 = 0x8000);
PROVIDE(__prg_rom_39 = 0x8000);
PROVIDE(__prg_rom_40 = 0x8000);
PROVIDE(__prg_rom_41 = 0x8000);
PROVIDE(__prg_rom_42 = 0x8000);
PROVIDE(__prg_rom_43 = 0x8000);
PROVIDE(__prg_rom_44 = 0x8000);
PROVIDE(__prg_rom_45 = 0x8000);
PROVIDE(__prg_rom_46 = 0x8000);
PROVIDE(__prg_rom_47 = 0x8000);
PROVIDE(__prg_rom_48 = 0x8000);
PROVIDE(__prg_rom_49 = 0x8000);
PROVIDE(__prg_rom_50 = 0x8000);
PROVIDE(__prg_rom_51 = 0x8000);
PROVIDE(__prg_rom_52 = 0x8000);
PROVIDE(__prg_rom_53 = 0x8000);
PROVIDE(__prg_rom_54 = 0x8000);
PROVIDE(__prg_rom_55 = 0x8000);
PROVIDE(__prg_rom_56 = 0x8000);
PROVIDE(__prg_rom_57 = 0x8000);
PROVIDE(__prg_rom_58 = 0x8000);
PROVIDE(__prg_rom_59 = 0x8000);
PROVIDE(__prg_rom_60 = 0x8000);

INCLUDE _prg-rom-banked.ld

/* This bank must be switched to on reset to establish a 24KiB fixed region. */
__fixed_bank = (__prg_rom_size / 8) - 3;

INPUT(reset-banked-8.o)

__prg_rom_fixed_lma = 0xa000;
__prg_rom_fixed_offset = __prg_rom_size * 1024 - 0x6000;

MEMORY { prg_rom_fixed : ORIGIN = __prg_rom_fixed_lma, LENGTH = 0x6000 }
REGION_ALIAS("c_rom", prg_rom_fixed)

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
  FULL(prg_rom_fixed)
  FULL(chr_rom)
}
