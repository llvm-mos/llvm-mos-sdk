ASSERT(__prg_rom_size > 32,
       "For less than 32KiB of PRG-ROM, use fixed banking.");

/* This bank must be switched to on reset to establish a 24KiB fixed region. */
__fixed_bank = (__prg_rom_size / 8) - 3;

INPUT(reset-banked-8.o)

MEMORY {
  prg_rom_fixed_lma : ORIGIN = 0x01000000 + __prg_rom_size * 1024 - 0x6000,
                      LENGTH = 0x6000

  prg_rom_0_vma     : ORIGIN = 0x008000, LENGTH = 0x2000
  prg_rom_1_vma     : ORIGIN = 0x018000, LENGTH = 0x2000
  prg_rom_2_vma     : ORIGIN = 0x028000, LENGTH = 0x2000
  prg_rom_3_vma     : ORIGIN = 0x038000, LENGTH = 0x2000
  prg_rom_4_vma     : ORIGIN = 0x048000, LENGTH = 0x2000
  prg_rom_5_vma     : ORIGIN = 0x058000, LENGTH = 0x2000
  prg_rom_6_vma     : ORIGIN = 0x068000, LENGTH = 0x2000
  prg_rom_7_vma     : ORIGIN = 0x078000, LENGTH = 0x2000
  prg_rom_8_vma     : ORIGIN = 0x088000, LENGTH = 0x2000
  prg_rom_9_vma     : ORIGIN = 0x098000, LENGTH = 0x2000
  prg_rom_10_vma    : ORIGIN = 0x0a8000, LENGTH = 0x2000
  prg_rom_11_vma    : ORIGIN = 0x0b8000, LENGTH = 0x2000
  prg_rom_12_vma    : ORIGIN = 0x0c8000, LENGTH = 0x2000
  prg_rom_13_vma    : ORIGIN = 0x0d8000, LENGTH = 0x2000
  prg_rom_14_vma    : ORIGIN = 0x0e8000, LENGTH = 0x2000
  prg_rom_15_vma    : ORIGIN = 0x0f8000, LENGTH = 0x2000
  prg_rom_16_vma    : ORIGIN = 0x108000, LENGTH = 0x2000
  prg_rom_17_vma    : ORIGIN = 0x118000, LENGTH = 0x2000
  prg_rom_18_vma    : ORIGIN = 0x128000, LENGTH = 0x2000
  prg_rom_19_vma    : ORIGIN = 0x138000, LENGTH = 0x2000
  prg_rom_20_vma    : ORIGIN = 0x148000, LENGTH = 0x2000
  prg_rom_21_vma    : ORIGIN = 0x158000, LENGTH = 0x2000
  prg_rom_22_vma    : ORIGIN = 0x168000, LENGTH = 0x2000
  prg_rom_23_vma    : ORIGIN = 0x178000, LENGTH = 0x2000
  prg_rom_24_vma    : ORIGIN = 0x188000, LENGTH = 0x2000
  prg_rom_25_vma    : ORIGIN = 0x198000, LENGTH = 0x2000
  prg_rom_26_vma    : ORIGIN = 0x1a8000, LENGTH = 0x2000
  prg_rom_27_vma    : ORIGIN = 0x1b8000, LENGTH = 0x2000
  prg_rom_28_vma    : ORIGIN = 0x1c8000, LENGTH = 0x2000
  prg_rom_29_vma    : ORIGIN = 0x1d8000, LENGTH = 0x2000
  prg_rom_30_vma    : ORIGIN = 0x1e8000, LENGTH = 0x2000
  prg_rom_31_vma    : ORIGIN = 0x1f8000, LENGTH = 0x2000
  prg_rom_32_vma    : ORIGIN = 0x208000, LENGTH = 0x2000
  prg_rom_33_vma    : ORIGIN = 0x218000, LENGTH = 0x2000
  prg_rom_34_vma    : ORIGIN = 0x228000, LENGTH = 0x2000
  prg_rom_35_vma    : ORIGIN = 0x238000, LENGTH = 0x2000
  prg_rom_36_vma    : ORIGIN = 0x248000, LENGTH = 0x2000
  prg_rom_37_vma    : ORIGIN = 0x258000, LENGTH = 0x2000
  prg_rom_38_vma    : ORIGIN = 0x268000, LENGTH = 0x2000
  prg_rom_39_vma    : ORIGIN = 0x278000, LENGTH = 0x2000
  prg_rom_40_vma    : ORIGIN = 0x288000, LENGTH = 0x2000
  prg_rom_41_vma    : ORIGIN = 0x298000, LENGTH = 0x2000
  prg_rom_42_vma    : ORIGIN = 0x2a8000, LENGTH = 0x2000
  prg_rom_43_vma    : ORIGIN = 0x2b8000, LENGTH = 0x2000
  prg_rom_44_vma    : ORIGIN = 0x2c8000, LENGTH = 0x2000
  prg_rom_45_vma    : ORIGIN = 0x2d8000, LENGTH = 0x2000
  prg_rom_46_vma    : ORIGIN = 0x2e8000, LENGTH = 0x2000
  prg_rom_47_vma    : ORIGIN = 0x2f8000, LENGTH = 0x2000
  prg_rom_48_vma    : ORIGIN = 0x308000, LENGTH = 0x2000
  prg_rom_49_vma    : ORIGIN = 0x318000, LENGTH = 0x2000
  prg_rom_50_vma    : ORIGIN = 0x328000, LENGTH = 0x2000
  prg_rom_51_vma    : ORIGIN = 0x338000, LENGTH = 0x2000
  prg_rom_52_vma    : ORIGIN = 0x348000, LENGTH = 0x2000
  prg_rom_53_vma    : ORIGIN = 0x358000, LENGTH = 0x2000
  prg_rom_54_vma    : ORIGIN = 0x368000, LENGTH = 0x2000
  prg_rom_55_vma    : ORIGIN = 0x378000, LENGTH = 0x2000
  prg_rom_56_vma    : ORIGIN = 0x388000, LENGTH = 0x2000
  prg_rom_57_vma    : ORIGIN = 0x398000, LENGTH = 0x2000
  prg_rom_58_vma    : ORIGIN = 0x3a8000, LENGTH = 0x2000
  prg_rom_59_vma    : ORIGIN = 0x3b8000, LENGTH = 0x2000
  prg_rom_60_vma    : ORIGIN = 0x3c8000, LENGTH = 0x2000

  prg_rom_fixed_vma : ORIGIN = 0xa000,   LENGTH = 0x6000
}

REGION_ALIAS("c_rom_vma", prg_rom_fixed_vma)
REGION_ALIAS("c_rom_lma", prg_rom_fixed_lma)

INCLUDE dpcm.ld
INCLUDE _reset.ld
