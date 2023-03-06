/* NES-MMC1 iNES file linker script. */

INCLUDE nes.ld

ASSERT(__chr_rom_size <= 128, "MMC1 only supports up to 128 KiB of CHR-ROM.")

ASSERT(__chr_ram_size + __chr_nvram_size <= 8,
       "MMC1 only supports up to 8KiB of CHR-(NV)RAM.")
ASSERT(__chr_ram_size % 4 == 0,
       "MMC1 CHR-RAM must come in 4KiB banks")
ASSERT(__chr_nvram_size % 4 == 0,
       "MMC1 CHR-RAM must come in 4KiB banks")

ASSERT(__prg_ram_size % 8 == 0,
       "MMC1 PRG-RAM must come in 8KiB banks")
ASSERT(__prg_nvram_size % 8 == 0,
       "MMC1 PRG-NVRAM must come in 8KiB banks")
ASSERT(__prg_ram_size + __prg_nvram_size <= 32,
       "MMC1 only supports up to 32KiB of PRG-(NV)RAM.")

MEMORY {
  prg_ram_0 : ORIGIN = 0x006000, LENGTH = __prg_ram_size + __prg_nvram_size >= 8  ? 0x2000 : 0
  prg_ram_1 : ORIGIN = 0x016000, LENGTH = __prg_ram_size + __prg_nvram_size >= 16 ? 0x2000 : 0
  prg_ram_2 : ORIGIN = 0x026000, LENGTH = __prg_ram_size + __prg_nvram_size >= 32 ? 0x2000 : 0
  prg_ram_3 : ORIGIN = 0x036000, LENGTH = __prg_ram_size + __prg_nvram_size >= 32 ? 0x2000 : 0

  chr_rom_0  : ORIGIN = 0x01000000, LENGTH = __chr_rom_size >= 4   ? 0x1000 : 0
  chr_rom_1  : ORIGIN = 0x01001000, LENGTH = __chr_rom_size >= 8   ? 0x1000 : 0
  chr_rom_2  : ORIGIN = 0x01002000, LENGTH = __chr_rom_size >= 16  ? 0x1000 : 0
  chr_rom_3  : ORIGIN = 0x01003000, LENGTH = __chr_rom_size >= 16  ? 0x1000 : 0
  chr_rom_4  : ORIGIN = 0x01004000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_5  : ORIGIN = 0x01005000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_6  : ORIGIN = 0x01006000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_7  : ORIGIN = 0x01007000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_8  : ORIGIN = 0x01008000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_9  : ORIGIN = 0x01009000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_10 : ORIGIN = 0x0100a000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_11 : ORIGIN = 0x0100b000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_12 : ORIGIN = 0x0100c000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_13 : ORIGIN = 0x0100d000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_14 : ORIGIN = 0x0100e000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_15 : ORIGIN = 0x0100f000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_16 : ORIGIN = 0x01010000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_17 : ORIGIN = 0x01011000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_18 : ORIGIN = 0x01012000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_19 : ORIGIN = 0x01013000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_20 : ORIGIN = 0x01014000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_21 : ORIGIN = 0x01015000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_22 : ORIGIN = 0x01016000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_23 : ORIGIN = 0x01017000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_24 : ORIGIN = 0x01018000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_25 : ORIGIN = 0x01019000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_26 : ORIGIN = 0x0101a000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_27 : ORIGIN = 0x0101b000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_28 : ORIGIN = 0x0101c000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_29 : ORIGIN = 0x0101d000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_30 : ORIGIN = 0x0101e000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_31 : ORIGIN = 0x0101f000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0

  chr_rom_0_1   : ORIGIN = 0x01000000, LENGTH = __chr_rom_size >= 8   ? 0x2000 : 0
  chr_rom_2_3   : ORIGIN = 0x01002000, LENGTH = __chr_rom_size >= 16  ? 0x2000 : 0
  chr_rom_4_5   : ORIGIN = 0x01004000, LENGTH = __chr_rom_size >= 32  ? 0x2000 : 0
  chr_rom_6_7   : ORIGIN = 0x01006000, LENGTH = __chr_rom_size >= 32  ? 0x2000 : 0
  chr_rom_8_9   : ORIGIN = 0x01008000, LENGTH = __chr_rom_size >= 64  ? 0x2000 : 0
  chr_rom_10_11 : ORIGIN = 0x0100a000, LENGTH = __chr_rom_size >= 64  ? 0x2000 : 0
  chr_rom_12_13 : ORIGIN = 0x0100c000, LENGTH = __chr_rom_size >= 64  ? 0x2000 : 0
  chr_rom_14_15 : ORIGIN = 0x0100e000, LENGTH = __chr_rom_size >= 64  ? 0x2000 : 0
  chr_rom_16_17 : ORIGIN = 0x01010000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_18_19 : ORIGIN = 0x01012000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_20_21 : ORIGIN = 0x01014000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_22_23 : ORIGIN = 0x01016000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_24_25 : ORIGIN = 0x01018000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_26_27 : ORIGIN = 0x0101a000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_28_29 : ORIGIN = 0x0101c000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
  chr_rom_30_31 : ORIGIN = 0x0101e000, LENGTH = __chr_rom_size >= 128 ? 0x2000 : 0
}

SECTIONS {
  .prg_ram_0 (NOLOAD) : { *(.prg_ram_0 .prg_ram_0.*) } >prg_ram_0
  .prg_ram_1 (NOLOAD) : { *(.prg_ram_1 .prg_ram_1.*) } >prg_ram_1
  .prg_ram_2 (NOLOAD) : { *(.prg_ram_2 .prg_ram_2.*) } >prg_ram_2
  .prg_ram_3 (NOLOAD) : { *(.prg_ram_3 .prg_ram_3.*) } >prg_ram_3

  .chr_rom_0  : { KEEP(*(.chr_rom_0 .chr_rom_0.*)) } >chr_rom_0
  .chr_rom_1  : { KEEP(*(.chr_rom_1 .chr_rom_1.*)) } >chr_rom_1
  .chr_rom_2  : { KEEP(*(.chr_rom_2 .chr_rom_2.*)) } >chr_rom_2
  .chr_rom_3  : { KEEP(*(.chr_rom_3 .chr_rom_3.*)) } >chr_rom_3
  .chr_rom_4  : { KEEP(*(.chr_rom_4 .chr_rom_4.*)) } >chr_rom_4
  .chr_rom_5  : { KEEP(*(.chr_rom_5 .chr_rom_5.*)) } >chr_rom_5
  .chr_rom_6  : { KEEP(*(.chr_rom_6 .chr_rom_6.*)) } >chr_rom_6
  .chr_rom_7  : { KEEP(*(.chr_rom_7 .chr_rom_7.*)) } >chr_rom_7
  .chr_rom_8  : { KEEP(*(.chr_rom_8 .chr_rom_8.*)) } >chr_rom_8
  .chr_rom_9  : { KEEP(*(.chr_rom_9 .chr_rom_9.*)) } >chr_rom_9
  .chr_rom_10 : { KEEP(*(.chr_rom_10 .chr_rom_10.*)) } >chr_rom_10
  .chr_rom_11 : { KEEP(*(.chr_rom_11 .chr_rom_11.*)) } >chr_rom_11
  .chr_rom_12 : { KEEP(*(.chr_rom_12 .chr_rom_12.*)) } >chr_rom_12
  .chr_rom_13 : { KEEP(*(.chr_rom_13 .chr_rom_13.*)) } >chr_rom_13
  .chr_rom_14 : { KEEP(*(.chr_rom_14 .chr_rom_14.*)) } >chr_rom_14
  .chr_rom_15 : { KEEP(*(.chr_rom_15 .chr_rom_15.*)) } >chr_rom_15
  .chr_rom_16 : { KEEP(*(.chr_rom_16 .chr_rom_16.*)) } >chr_rom_16
  .chr_rom_17 : { KEEP(*(.chr_rom_17 .chr_rom_17.*)) } >chr_rom_17
  .chr_rom_18 : { KEEP(*(.chr_rom_18 .chr_rom_18.*)) } >chr_rom_18
  .chr_rom_19 : { KEEP(*(.chr_rom_19 .chr_rom_19.*)) } >chr_rom_19
  .chr_rom_20 : { KEEP(*(.chr_rom_20 .chr_rom_20.*)) } >chr_rom_20
  .chr_rom_21 : { KEEP(*(.chr_rom_21 .chr_rom_21.*)) } >chr_rom_21
  .chr_rom_22 : { KEEP(*(.chr_rom_22 .chr_rom_22.*)) } >chr_rom_22
  .chr_rom_23 : { KEEP(*(.chr_rom_23 .chr_rom_23.*)) } >chr_rom_23
  .chr_rom_24 : { KEEP(*(.chr_rom_24 .chr_rom_24.*)) } >chr_rom_24
  .chr_rom_25 : { KEEP(*(.chr_rom_25 .chr_rom_25.*)) } >chr_rom_25
  .chr_rom_26 : { KEEP(*(.chr_rom_26 .chr_rom_26.*)) } >chr_rom_26
  .chr_rom_27 : { KEEP(*(.chr_rom_27 .chr_rom_27.*)) } >chr_rom_27
  .chr_rom_28 : { KEEP(*(.chr_rom_28 .chr_rom_28.*)) } >chr_rom_28
  .chr_rom_29 : { KEEP(*(.chr_rom_29 .chr_rom_29.*)) } >chr_rom_29
  .chr_rom_30 : { KEEP(*(.chr_rom_30 .chr_rom_30.*)) } >chr_rom_30
  .chr_rom_31 : { KEEP(*(.chr_rom_31 .chr_rom_31.*)) } >chr_rom_31

  .chr_rom_0_1   : { KEEP(*(.chr_rom_0_1   .chr_rom_0_1.*)) }   >chr_rom_0_1
  .chr_rom_2_3   : { KEEP(*(.chr_rom_2_3   .chr_rom_2_3.*)) }   >chr_rom_2_3
  .chr_rom_4_5   : { KEEP(*(.chr_rom_4_5   .chr_rom_4_5.*)) }   >chr_rom_4_5
  .chr_rom_6_7   : { KEEP(*(.chr_rom_6_7   .chr_rom_6_7.*)) }   >chr_rom_6_7
  .chr_rom_8_9   : { KEEP(*(.chr_rom_8_9   .chr_rom_8_9.*)) }   >chr_rom_8_9
  .chr_rom_10_11 : { KEEP(*(.chr_rom_10_11 .chr_rom_10_11.*)) } >chr_rom_10_11
  .chr_rom_12_13 : { KEEP(*(.chr_rom_12_13 .chr_rom_12_13.*)) } >chr_rom_12_13
  .chr_rom_14_15 : { KEEP(*(.chr_rom_14_15 .chr_rom_14_15.*)) } >chr_rom_14_15
  .chr_rom_16_17 : { KEEP(*(.chr_rom_16_17 .chr_rom_16_17.*)) } >chr_rom_16_17
  .chr_rom_18_19 : { KEEP(*(.chr_rom_18_19 .chr_rom_18_19.*)) } >chr_rom_18_19
  .chr_rom_20_21 : { KEEP(*(.chr_rom_20_21 .chr_rom_20_21.*)) } >chr_rom_20_21
  .chr_rom_22_23 : { KEEP(*(.chr_rom_22_23 .chr_rom_22_23.*)) } >chr_rom_22_23
  .chr_rom_24_25 : { KEEP(*(.chr_rom_24_25 .chr_rom_24_25.*)) } >chr_rom_24_25
  .chr_rom_26_27 : { KEEP(*(.chr_rom_26_27 .chr_rom_26_27.*)) } >chr_rom_26_27
  .chr_rom_28_29 : { KEEP(*(.chr_rom_28_29 .chr_rom_28_29.*)) } >chr_rom_28_29
  .chr_rom_30_31 : { KEEP(*(.chr_rom_30_31 .chr_rom_30_31.*)) } >chr_rom_30_31
}
