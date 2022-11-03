INCLUDE _prg-rom-banked-16-common.ld

INPUT(reset-banked-mode-0.o)

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
PROVIDE(__prg_rom_61 = 0xa000);

MEMORY {
  prg_rom_fixed_lma : ORIGIN = 0x01000000 + __prg_rom_size * 1024 - 0x4000,
                      LENGTH = 0x4000
  prg_rom_fixed_vma : ORIGIN = 0xc000, LENGTH = 0x4000
}

REGION_ALIAS("c_rom_vma", prg_rom_fixed_vma)
REGION_ALIAS("c_rom_lma", prg_rom_fixed_lma)
