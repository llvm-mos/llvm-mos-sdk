/* NES-MMC1 iNES file linker script. */

INCLUDE nes.ld

ASSERT(__chr_rom_size <= 128, "MMC1 only supports up to 128 KiB of CHR-ROM.")
ASSERT(__chr_rom_size == 0 || __chr_rom_size == 1 << LOG2CEIL(__chr_rom_size),
         "MMC1 only supports CHR-ROM sizes that are powers of two.")

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
  /* PRG-ROM VMAs. */
  prg_ram_0_vma : ORIGIN = 0x6000, LENGTH = 0x2000
  prg_ram_1_vma : ORIGIN = 0x6000, LENGTH = 0x2000
  prg_ram_2_vma : ORIGIN = 0x6000, LENGTH = 0x2000
  prg_ram_3_vma : ORIGIN = 0x6000, LENGTH = 0x2000

  /* PRG-ROM LMAs. Just performs a size check on the contents and appeases the
   * linker. */
  prg_ram_0_lma : ORIGIN = 0x03000000, LENGTH = __prg_ram_size + __prg_nvram_size >= 8  ? 0x2000 : 0
  prg_ram_1_lma : ORIGIN = 0x03002000, LENGTH = __prg_ram_size + __prg_nvram_size >= 16 ? 0x2000 : 0
  prg_ram_2_lma : ORIGIN = 0x03004000, LENGTH = __prg_ram_size + __prg_nvram_size >= 32 ? 0x2000 : 0
  prg_ram_3_lma : ORIGIN = 0x03006000, LENGTH = __prg_ram_size + __prg_nvram_size >= 32 ? 0x2000 : 0

  /* CHR-ROM bank LMAs. */
  chr_rom_0  : ORIGIN = 0x02000000, LENGTH = __chr_rom_size >= 4   ? 0x1000 : 0
  chr_rom_1  : ORIGIN = 0x02001000, LENGTH = __chr_rom_size >= 8   ? 0x1000 : 0
  chr_rom_2  : ORIGIN = 0x02002000, LENGTH = __chr_rom_size >= 16  ? 0x1000 : 0
  chr_rom_3  : ORIGIN = 0x02003000, LENGTH = __chr_rom_size >= 16  ? 0x1000 : 0
  chr_rom_4  : ORIGIN = 0x02004000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_5  : ORIGIN = 0x02005000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_6  : ORIGIN = 0x02006000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_7  : ORIGIN = 0x02007000, LENGTH = __chr_rom_size >= 32  ? 0x1000 : 0
  chr_rom_8  : ORIGIN = 0x02008000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_9  : ORIGIN = 0x02009000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_10 : ORIGIN = 0x0200a000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_11 : ORIGIN = 0x0200b000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_12 : ORIGIN = 0x0200c000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_13 : ORIGIN = 0x0200d000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_14 : ORIGIN = 0x0200e000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_15 : ORIGIN = 0x0200f000, LENGTH = __chr_rom_size >= 64  ? 0x1000 : 0
  chr_rom_16 : ORIGIN = 0x02010000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_17 : ORIGIN = 0x02011000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_18 : ORIGIN = 0x02012000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_19 : ORIGIN = 0x02013000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_20 : ORIGIN = 0x02014000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_21 : ORIGIN = 0x02015000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_22 : ORIGIN = 0x02016000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_23 : ORIGIN = 0x02017000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_24 : ORIGIN = 0x02018000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_25 : ORIGIN = 0x02019000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_26 : ORIGIN = 0x0201a000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_27 : ORIGIN = 0x0201b000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_28 : ORIGIN = 0x0201c000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_29 : ORIGIN = 0x0201d000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_30 : ORIGIN = 0x0201e000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
  chr_rom_31 : ORIGIN = 0x0201f000, LENGTH = __chr_rom_size >= 128 ? 0x1000 : 0
}

SECTIONS {
  .prg_ram_0 (NOLOAD) : OVERLAY { *(.prg_ram_0 .prg_ram_0.*) } >prg_ram_0_vma AT>prg_ram_0_lma
  .prg_ram_1 (NOLOAD) : OVERLAY { *(.prg_ram_1 .prg_ram_1.*) } >prg_ram_1_vma AT>prg_ram_1_lma
  .prg_ram_2 (NOLOAD) : OVERLAY { *(.prg_ram_2 .prg_ram_2.*) } >prg_ram_2_vma AT>prg_ram_2_lma
  .prg_ram_3 (NOLOAD) : OVERLAY { *(.prg_ram_3 .prg_ram_3.*) } >prg_ram_3_vma AT>prg_ram_3_lma

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
}

INCLUDE ines.ld
