/* Common elements of NES-NROM iNES file linker scripts. */

INCLUDE nes.ld

ASSERT(__prg_ram_size == 0 || __prg_nvram_size == 0,
       "Simulatenously using PRG-RAM and PRG-NVRAM is not supported.")
ASSERT(__chr_rom_size <= 128, "MMC1 only supports up to 128 KiB of CHR-ROM.")
ASSERT(__prg_rom_size >= 32, "MMC1 requires at least 32KiB of PRG-ROM.")
ASSERT(__prg_rom_size <= 512, "MMC1 only supports up to 512KiB PRG-ROM.")
ASSERT(__prg_rom_size <= 256 || __chr_rom_size <= 64,
       "MMC1 cannot support both >256 KiB of PRG-RAM and >64KiB of CHR-ROM")
ASSERT(__prg_ram_size + __prg_nvram_size <= 32,
       "At most 32 KiB of PRG-(NV)RAM is supported.")
ASSERT((__prg_ram_size + __prg_nvram_size) % 8 == 0,
       "PRG-(NV)RAM size must be divisible by 8KiB")

MEMORY {
  /* PRG-RAM VMA. */
  prg_ram : ORIGIN = 0x6000,
            LENGTH = MAX(0x2000, (__prg_ram_size + __prg_nvram_size) * 1024)

  /* PRG-ROM VMAs. */
  prg_rom_lo : ORIGIN = 0x8000, LENGTH = 0x4000
  prg_rom_hi : ORIGIN = 0xc000, LENGTH = 0x4000

  /* PRG-ROM LMA. */
  prg_rom : ORIGIN = 0x10000, LENGTH = __prg_rom_size * 1024

  /* 16 KiB banks. */
  prg_rom_0  : ORIGIN = 0x10000, LENGTH = 0x4000
  prg_rom_1  : ORIGIN = 0x14000, LENGTH = 0x4000
  prg_rom_2  : ORIGIN = 0x18000, LENGTH = 0x4000
  prg_rom_3  : ORIGIN = 0x1c000, LENGTH = 0x4000
  prg_rom_4  : ORIGIN = 0x20000, LENGTH = 0x4000
  prg_rom_5  : ORIGIN = 0x24000, LENGTH = 0x4000
  prg_rom_6  : ORIGIN = 0x28000, LENGTH = 0x4000
  prg_rom_7  : ORIGIN = 0x2c000, LENGTH = 0x4000
  prg_rom_8  : ORIGIN = 0x30000, LENGTH = 0x4000
  prg_rom_9  : ORIGIN = 0x34000, LENGTH = 0x4000
  prg_rom_10 : ORIGIN = 0x38000, LENGTH = 0x4000
  prg_rom_11 : ORIGIN = 0x3c000, LENGTH = 0x4000
  prg_rom_12 : ORIGIN = 0x40000, LENGTH = 0x4000
  prg_rom_13 : ORIGIN = 0x44000, LENGTH = 0x4000
  prg_rom_14 : ORIGIN = 0x48000, LENGTH = 0x4000
  /* Accessible at startup at VMA prg_rom_hi. */
  prg_rom_15 : ORIGIN = 0x4c000, LENGTH = 0x4000
  prg_rom_16 : ORIGIN = 0x50000, LENGTH = 0x4000
  prg_rom_17 : ORIGIN = 0x54000, LENGTH = 0x4000
  prg_rom_18 : ORIGIN = 0x58000, LENGTH = 0x4000
  prg_rom_19 : ORIGIN = 0x5c000, LENGTH = 0x4000
  prg_rom_20 : ORIGIN = 0x60000, LENGTH = 0x4000
  prg_rom_21 : ORIGIN = 0x64000, LENGTH = 0x4000
  prg_rom_22 : ORIGIN = 0x68000, LENGTH = 0x4000
  prg_rom_23 : ORIGIN = 0x6c000, LENGTH = 0x4000
  prg_rom_24 : ORIGIN = 0x70000, LENGTH = 0x4000
  prg_rom_25 : ORIGIN = 0x74000, LENGTH = 0x4000
  prg_rom_26 : ORIGIN = 0x78000, LENGTH = 0x4000
  prg_rom_27 : ORIGIN = 0x7c000, LENGTH = 0x4000
  prg_rom_28 : ORIGIN = 0x80000, LENGTH = 0x4000
  prg_rom_29 : ORIGIN = 0x84000, LENGTH = 0x4000
  prg_rom_30 : ORIGIN = 0x88000, LENGTH = 0x4000
  prg_rom_31 : ORIGIN = 0x8c000, LENGTH = 0x4000
  /* 32 KiB banks. */
  prg_rom_0_1   : ORIGIN = 0x10000, LENGTH = 0x8000
  prg_rom_2_3   : ORIGIN = 0x18000, LENGTH = 0x8000
  prg_rom_4_5   : ORIGIN = 0x20000, LENGTH = 0x8000
  prg_rom_6_7   : ORIGIN = 0x28000, LENGTH = 0x8000
  prg_rom_8_9   : ORIGIN = 0x30000, LENGTH = 0x8000
  prg_rom_10_11 : ORIGIN = 0x38000, LENGTH = 0x8000
  prg_rom_12_13 : ORIGIN = 0x40000, LENGTH = 0x8000
  prg_rom_14_15 : ORIGIN = 0x48000, LENGTH = 0x8000
  prg_rom_16_17 : ORIGIN = 0x50000, LENGTH = 0x8000
  prg_rom_18_19 : ORIGIN = 0x58000, LENGTH = 0x8000
  prg_rom_20_21 : ORIGIN = 0x60000, LENGTH = 0x8000
  prg_rom_22_23 : ORIGIN = 0x68000, LENGTH = 0x8000
  prg_rom_24_25 : ORIGIN = 0x70000, LENGTH = 0x8000
  prg_rom_26_27 : ORIGIN = 0x78000, LENGTH = 0x8000
  prg_rom_28_29 : ORIGIN = 0x80000, LENGTH = 0x8000
  prg_rom_30_31 : ORIGIN = 0x88000, LENGTH = 0x8000

  /* CHR-ROM LMA. */
  chr_rom : ORIGIN = 0x90000, LENGTH = __chr_rom_size * 1024

  /* 4 KiB Banks */
  chr_rom_0  : ORIGIN = 0x90000, LENGTH = 0x1000
  chr_rom_1  : ORIGIN = 0x91000, LENGTH = 0x1000
  chr_rom_2  : ORIGIN = 0x92000, LENGTH = 0x1000
  chr_rom_3  : ORIGIN = 0x93000, LENGTH = 0x1000
  chr_rom_4  : ORIGIN = 0x94000, LENGTH = 0x1000
  chr_rom_5  : ORIGIN = 0x95000, LENGTH = 0x1000
  chr_rom_6  : ORIGIN = 0x96000, LENGTH = 0x1000
  chr_rom_7  : ORIGIN = 0x97000, LENGTH = 0x1000
  chr_rom_8  : ORIGIN = 0x98000, LENGTH = 0x1000
  chr_rom_9  : ORIGIN = 0x99000, LENGTH = 0x1000
  chr_rom_10 : ORIGIN = 0x9a000, LENGTH = 0x1000
  chr_rom_11 : ORIGIN = 0x9b000, LENGTH = 0x1000
  chr_rom_12 : ORIGIN = 0x9c000, LENGTH = 0x1000
  chr_rom_13 : ORIGIN = 0x9d000, LENGTH = 0x1000
  chr_rom_14 : ORIGIN = 0x9e000, LENGTH = 0x1000
  chr_rom_15 : ORIGIN = 0x9f000, LENGTH = 0x1000
  chr_rom_16 : ORIGIN = 0xa0000, LENGTH = 0x1000
  chr_rom_17 : ORIGIN = 0xa1000, LENGTH = 0x1000
  chr_rom_18 : ORIGIN = 0xa2000, LENGTH = 0x1000
  chr_rom_19 : ORIGIN = 0xa3000, LENGTH = 0x1000
  chr_rom_20 : ORIGIN = 0xa4000, LENGTH = 0x1000
  chr_rom_21 : ORIGIN = 0xa5000, LENGTH = 0x1000
  chr_rom_22 : ORIGIN = 0xa6000, LENGTH = 0x1000
  chr_rom_23 : ORIGIN = 0xa7000, LENGTH = 0x1000
  chr_rom_24 : ORIGIN = 0xa8000, LENGTH = 0x1000
  chr_rom_25 : ORIGIN = 0xa9000, LENGTH = 0x1000
  chr_rom_26 : ORIGIN = 0xaa000, LENGTH = 0x1000
  chr_rom_27 : ORIGIN = 0xab000, LENGTH = 0x1000
  chr_rom_28 : ORIGIN = 0xac000, LENGTH = 0x1000
  chr_rom_29 : ORIGIN = 0xad000, LENGTH = 0x1000
  chr_rom_30 : ORIGIN = 0xae000, LENGTH = 0x1000
  chr_rom_31 : ORIGIN = 0xaf000, LENGTH = 0x1000

  /* 8 KiB Banks */
  chr_rom_0_1   : ORIGIN = 0x90000, LENGTH = 0x2000
  chr_rom_2_3   : ORIGIN = 0x92000, LENGTH = 0x2000
  chr_rom_4_5   : ORIGIN = 0x94000, LENGTH = 0x2000
  chr_rom_6_7   : ORIGIN = 0x96000, LENGTH = 0x2000
  chr_rom_8_9   : ORIGIN = 0x98000, LENGTH = 0x2000
  chr_rom_10_11 : ORIGIN = 0x9a000, LENGTH = 0x2000
  chr_rom_12_13 : ORIGIN = 0x9c000, LENGTH = 0x2000
  chr_rom_14_15 : ORIGIN = 0x9e000, LENGTH = 0x2000
  chr_rom_16_17 : ORIGIN = 0xa0000, LENGTH = 0x2000
  chr_rom_18_19 : ORIGIN = 0xa2000, LENGTH = 0x2000
  chr_rom_20_21 : ORIGIN = 0xa4000, LENGTH = 0x2000
  chr_rom_22_23 : ORIGIN = 0xa6000, LENGTH = 0x2000
  chr_rom_24_25 : ORIGIN = 0xa8000, LENGTH = 0x2000
  chr_rom_26_27 : ORIGIN = 0xaa000, LENGTH = 0x2000
  chr_rom_28_29 : ORIGIN = 0xac000, LENGTH = 0x2000
  chr_rom_30_31 : ORIGIN = 0xae000, LENGTH = 0x2000
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram

  .prg_rom_0 : { *(.prg_rom_0 .prg_rom_0.*) } >prg_rom_0_vma AT>prg_rom_0
  .prg_rom_1 : { *(.prg_rom_1 .prg_rom_1.*) } >prg_rom_1_vma AT>prg_rom_1
  .prg_rom_2 : { *(.prg_rom_2 .prg_rom_2.*) } >prg_rom_2_vma AT>prg_rom_2
  .prg_rom_3 : { *(.prg_rom_3 .prg_rom_3.*) } >prg_rom_3_vma AT>prg_rom_3
  .prg_rom_4 : { *(.prg_rom_4 .prg_rom_4.*) } >prg_rom_4_vma AT>prg_rom_4
  .prg_rom_5 : { *(.prg_rom_5 .prg_rom_5.*) } >prg_rom_5_vma AT>prg_rom_5
  .prg_rom_6 : { *(.prg_rom_6 .prg_rom_6.*) } >prg_rom_6_vma AT>prg_rom_6
  .prg_rom_7 : { *(.prg_rom_7 .prg_rom_7.*) } >prg_rom_7_vma AT>prg_rom_7
  .prg_rom_8 : { *(.prg_rom_8 .prg_rom_8.*) } >prg_rom_8_vma AT>prg_rom_8
  .prg_rom_9 : { *(.prg_rom_9 .prg_rom_9.*) } >prg_rom_9_vma AT>prg_rom_9
  .prg_rom_10 : { *(.prg_rom_10 .prg_rom_10.*) } >prg_rom_10_vma AT>prg_rom_10
  .prg_rom_11 : { *(.prg_rom_11 .prg_rom_11.*) } >prg_rom_11_vma AT>prg_rom_11
  .prg_rom_12 : { *(.prg_rom_12 .prg_rom_12.*) } >prg_rom_12_vma AT>prg_rom_12
  .prg_rom_13 : { *(.prg_rom_13 .prg_rom_13.*) } >prg_rom_13_vma AT>prg_rom_13
  .prg_rom_14 : { *(.prg_rom_14 .prg_rom_14.*) } >prg_rom_14_vma AT>prg_rom_14
  .prg_rom_15 : { *(.prg_rom_15 .prg_rom_15.*) } >prg_rom_15_vma AT>prg_rom_15
  .prg_rom_16 : { *(.prg_rom_16 .prg_rom_16.*) } >prg_rom_16_vma AT>prg_rom_16
  .prg_rom_17 : { *(.prg_rom_17 .prg_rom_17.*) } >prg_rom_17_vma AT>prg_rom_17
  .prg_rom_18 : { *(.prg_rom_18 .prg_rom_18.*) } >prg_rom_18_vma AT>prg_rom_18
  .prg_rom_19 : { *(.prg_rom_19 .prg_rom_19.*) } >prg_rom_19_vma AT>prg_rom_19
  .prg_rom_20 : { *(.prg_rom_20 .prg_rom_20.*) } >prg_rom_20_vma AT>prg_rom_20
  .prg_rom_21 : { *(.prg_rom_21 .prg_rom_21.*) } >prg_rom_21_vma AT>prg_rom_21
  .prg_rom_22 : { *(.prg_rom_22 .prg_rom_22.*) } >prg_rom_22_vma AT>prg_rom_22
  .prg_rom_23 : { *(.prg_rom_23 .prg_rom_23.*) } >prg_rom_23_vma AT>prg_rom_23
  .prg_rom_24 : { *(.prg_rom_24 .prg_rom_24.*) } >prg_rom_24_vma AT>prg_rom_24
  .prg_rom_25 : { *(.prg_rom_25 .prg_rom_25.*) } >prg_rom_25_vma AT>prg_rom_25
  .prg_rom_26 : { *(.prg_rom_26 .prg_rom_26.*) } >prg_rom_26_vma AT>prg_rom_26
  .prg_rom_27 : { *(.prg_rom_27 .prg_rom_27.*) } >prg_rom_27_vma AT>prg_rom_27
  .prg_rom_28 : { *(.prg_rom_28 .prg_rom_28.*) } >prg_rom_28_vma AT>prg_rom_28
  .prg_rom_29 : { *(.prg_rom_29 .prg_rom_29.*) } >prg_rom_29_vma AT>prg_rom_29
  .prg_rom_30 : { *(.prg_rom_30 .prg_rom_30.*) } >prg_rom_30_vma AT>prg_rom_30
  .prg_rom_31 : { *(.prg_rom_31 .prg_rom_31.*) } >prg_rom_31_vma AT>prg_rom_31
  .prg_rom_0_1 : { *(.prg_rom_0_1 .prg_rom_0_1.*) } >prg_rom_0_1_vma AT>prg_rom_0_1
  .prg_rom_2_3 : { *(.prg_rom_2_3 .prg_rom_2_3.*) } >prg_rom_2_3_vma AT>prg_rom_2_3
  .prg_rom_4_5 : { *(.prg_rom_4_5 .prg_rom_4_5.*) } >prg_rom_4_5_vma AT>prg_rom_4_5
  .prg_rom_6_7 : { *(.prg_rom_6_7 .prg_rom_6_7.*) } >prg_rom_6_7_vma AT>prg_rom_6_7
  .prg_rom_8_9 : { *(.prg_rom_8_9 .prg_rom_8_9.*) } >prg_rom_8_9_vma AT>prg_rom_8_9
  .prg_rom_10_11 : { *(.prg_rom_10_11 .prg_rom_10_11.*) } >prg_rom_10_11_vma AT>prg_rom_10_11
  .prg_rom_12_13 : { *(.prg_rom_12_13 .prg_rom_12_13.*) } >prg_rom_12_13_vma AT>prg_rom_12_13
  .prg_rom_14_15 : { *(.prg_rom_14_15 .prg_rom_14_15.*) } >prg_rom_14_15_vma AT>prg_rom_14_15
  .prg_rom_16_17 : { *(.prg_rom_16_17 .prg_rom_16_17.*) } >prg_rom_16_17_vma AT>prg_rom_16_17
  .prg_rom_18_19 : { *(.prg_rom_18_19 .prg_rom_18_19.*) } >prg_rom_18_19_vma AT>prg_rom_18_19
  .prg_rom_20_21 : { *(.prg_rom_20_21 .prg_rom_20_21.*) } >prg_rom_20_21_vma AT>prg_rom_20_21
  .prg_rom_22_23 : { *(.prg_rom_22_23 .prg_rom_22_23.*) } >prg_rom_22_23_vma AT>prg_rom_22_23
  .prg_rom_24_25 : { *(.prg_rom_24_25 .prg_rom_24_25.*) } >prg_rom_24_25_vma AT>prg_rom_24_25
  .prg_rom_26_27 : { *(.prg_rom_26_27 .prg_rom_26_27.*) } >prg_rom_26_27_vma AT>prg_rom_26_27
  .prg_rom_28_29 : { *(.prg_rom_28_29 .prg_rom_28_29.*) } >prg_rom_28_29_vma AT>prg_rom_28_29
  .prg_rom_30_31 : { *(.prg_rom_30_31 .prg_rom_30_31.*) } >prg_rom_30_31_vma AT>prg_rom_30_31

  /* Use this section to assign to the CHR-ROM banks all-at-once. */
  .chr_rom : { KEEP(*(.chr_rom .chr_rom.*)) } >chr_rom

  .chr_rom_0 : { KEEP(*(.chr_rom_0 .chr_rom_0.*)) } >chr_rom_0
  .chr_rom_1 : { KEEP(*(.chr_rom_1 .chr_rom_1.*)) } >chr_rom_1
  .chr_rom_2 : { KEEP(*(.chr_rom_2 .chr_rom_2.*)) } >chr_rom_2
  .chr_rom_3 : { KEEP(*(.chr_rom_3 .chr_rom_3.*)) } >chr_rom_3
  .chr_rom_4 : { KEEP(*(.chr_rom_4 .chr_rom_4.*)) } >chr_rom_4
  .chr_rom_5 : { KEEP(*(.chr_rom_5 .chr_rom_5.*)) } >chr_rom_5
  .chr_rom_6 : { KEEP(*(.chr_rom_6 .chr_rom_6.*)) } >chr_rom_6
  .chr_rom_7 : { KEEP(*(.chr_rom_7 .chr_rom_7.*)) } >chr_rom_7
  .chr_rom_8 : { KEEP(*(.chr_rom_8 .chr_rom_8.*)) } >chr_rom_8
  .chr_rom_9 : { KEEP(*(.chr_rom_9 .chr_rom_9.*)) } >chr_rom_9
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

  .chr_rom_0_1 : { KEEP(*(.chr_rom_0_1 .chr_rom_0_1.*)) } >chr_rom_0_1
  .chr_rom_2_3 : { KEEP(*(.chr_rom_2_3 .chr_rom_2_3.*)) } >chr_rom_2_3
  .chr_rom_4_5 : { KEEP(*(.chr_rom_4_5 .chr_rom_4_5.*)) } >chr_rom_4_5
  .chr_rom_6_7 : { KEEP(*(.chr_rom_6_7 .chr_rom_6_7.*)) } >chr_rom_6_7
  .chr_rom_8_9 : { KEEP(*(.chr_rom_8_9 .chr_rom_8_9.*)) } >chr_rom_8_9
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

  /* Init code must be loadable at startup, which means bank 15 @ 0xc000. */
  .init : { INCLUDE init-sections.ld } >prg_rom_hi AT>prg_rom_15
  .text : {
    INCLUDE fini-sections.ld
    INCLUDE text-sections-proper.ld
  } >c_rom_vma AT>c_rom
  .rodata : { INCLUDE rodata-sections.ld } >c_rom_vma AT>c_rom
  .data : { INCLUDE data-sections.ld } >c_ram AT>c_rom
  /* Don't reference c_rom in this expression, as it isn't defined yet. */
  __data_load_start = LOADADDR(.data) - LOADADDR(.rodata) + ADDR(.rodata);
  __data_size = SIZEOF(.data);
  .bss (NOLOAD) : { INCLUDE bss-sections.ld } >c_ram
  INCLUDE bss-symbols.ld
  .noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >c_ram
  .vector 0xfffa - ORIGIN(prg_rom_hi) + ORIGIN(prg_rom_15) : {
    SHORT(nmi) SHORT(_start) SHORT(irq)
  } >prg_rom_15
}

INCLUDE ines.ld
