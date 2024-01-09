/* Atari800 MegaCart and SIC! (bank-switched) cartridge linker script.

  Support for 16 KiB to 512 KiB MegaCart and SIC! cartridges.

  There are be "__cart_rom_size / 16 KiB" banks, mapped one at a time
  over the entire 16 KiB cartridge address space from 0x8000 through
  0xBFFF.  It is also possible to disable the cartridge to access
  underlying RAM.

  On power-up the bank0 is selected, however, SIC! cartridges-up will
  not have the lower 8 KiB enabled.  We use INIT to fix this and
  adjust MEMTOP if needed.

  https://github.com/atari800/atari800/blob/ATARI800_5_0_0/DOC/cart.txt
  has details. */

INPUT(tail0.o)

PROVIDE(__cart_rom_size = 512);

ASSERT(__cart_rom_size == 1 << LOG2CEIL(__cart_rom_size),
       "ATARI 800 MegaCart cartridge: __cart_rom_size size must be a power of 2.")
ASSERT(__cart_rom_size >= 16,
       "ATARI 800 MegaCart cartridge: __cart_rom_size size must be >= 16 KiB.")
ASSERT(__cart_rom_size <= 512,
       "ATARI 800 MegaCart cartridge: __cart_rom_size size must be <= 512 KiB.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* Memory as low as 0x700 works when not using DOS. Assume we have
     at most 8 KiB of RAM to maximize compatabilty with the earliest Atari 400
     model. */
  ram (w) : ORIGIN = 0x700, LENGTH = 0x2000 - 0x700
}

/* Provide imaginary (zero page) registers. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

/* LMAs */
__bank0_lma     = 0x01008000;
__bank1_lma     = 0x01018000;
__bank2_lma     = 0x01028000;
__bank3_lma     = 0x01038000;
__bank4_lma     = 0x01048000;
__bank5_lma     = 0x01058000;
__bank6_lma     = 0x01068000;
__bank7_lma     = 0x01078000;
__bank8_lma     = 0x01088000;
__bank9_lma     = 0x01098000;
__bank10_lma    = 0x010a8000;
__bank11_lma    = 0x010b8000;
__bank12_lma    = 0x010c8000;
__bank13_lma    = 0x010d8000;
__bank14_lma    = 0x010e8000;
__bank15_lma    = 0x010f8000;
__bank16_lma    = 0x01108000;
__bank17_lma    = 0x01118000;
__bank18_lma    = 0x01128000;
__bank19_lma    = 0x01138000;
__bank20_lma    = 0x01148000;
__bank21_lma    = 0x01158000;
__bank22_lma    = 0x01168000;
__bank23_lma    = 0x01178000;
__bank24_lma    = 0x01188000;
__bank25_lma    = 0x01198000;
__bank26_lma    = 0x011a8000;
__bank27_lma    = 0x011b8000;
__bank28_lma    = 0x011c8000;
__bank29_lma    = 0x011d8000;
__bank30_lma    = 0x011e8000;
__bank31_lma    = 0x011f8000;

MEMORY {
  /* bank0 is truncated by 20 bytes so we can add a tail */
  bank0         : ORIGIN = __bank0_lma,  LENGTH = 0x4000 - 20
  tail0         : ORIGIN = __bank0_lma + 0x4000 - 20, LENGTH = 20

  bank1         : ORIGIN = __bank1_lma,  LENGTH = __cart_rom_size >=  32 ? 0x4000 : 0
  bank2         : ORIGIN = __bank2_lma,  LENGTH = __cart_rom_size >=  64 ? 0x4000 : 0
  bank3         : ORIGIN = __bank3_lma,  LENGTH = __cart_rom_size >=  64 ? 0x4000 : 0
  bank4         : ORIGIN = __bank4_lma,  LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  bank5         : ORIGIN = __bank5_lma,  LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  bank6         : ORIGIN = __bank6_lma,  LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  bank7         : ORIGIN = __bank7_lma,  LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0

  bank8         : ORIGIN = __bank8_lma,  LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank9         : ORIGIN = __bank9_lma,  LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank10        : ORIGIN = __bank10_lma, LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank11        : ORIGIN = __bank11_lma, LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank12        : ORIGIN = __bank12_lma, LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank13        : ORIGIN = __bank13_lma, LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank14        : ORIGIN = __bank14_lma, LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0
  bank15        : ORIGIN = __bank15_lma, LENGTH = __cart_rom_size >= 256 ? 0x4000 : 0

  bank16        : ORIGIN = __bank16_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank17        : ORIGIN = __bank17_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank18        : ORIGIN = __bank18_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank19        : ORIGIN = __bank19_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank20        : ORIGIN = __bank20_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank21        : ORIGIN = __bank21_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank22        : ORIGIN = __bank22_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank23        : ORIGIN = __bank23_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank24        : ORIGIN = __bank24_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank25        : ORIGIN = __bank25_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank26        : ORIGIN = __bank26_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank27        : ORIGIN = __bank27_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank28        : ORIGIN = __bank28_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank29        : ORIGIN = __bank29_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank30        : ORIGIN = __bank30_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
  bank31        : ORIGIN = __bank31_lma, LENGTH = __cart_rom_size >= 512 ? 0x4000 : 0
}

REGION_ALIAS("c_writeable", ram)
REGION_ALIAS("c_readonly", bank0)

SECTIONS {
  INCLUDE c.ld

  /* Define a fixed section at the beginning of bank0. */
  .bank0_fixed : {
    *(.bank0_fixed .bank0_fixed.*)
    __bank0_fixed_end = .;
    __bank0_fixed_size = __bank0_fixed_end - __bank0_lma;
  } >bank0

  /* Offset other banks. */
  __bank1_fixed_size = __cart_rom_size >= 32 ? __bank0_fixed_size : 0;

  __bank2_fixed_size = __cart_rom_size >= 64 ? __bank0_fixed_size : 0;
  __bank3_fixed_size = __cart_rom_size >= 64 ? __bank0_fixed_size : 0;

  __bank4_fixed_size = __cart_rom_size >= 128 ? __bank0_fixed_size : 0;
  __bank5_fixed_size = __cart_rom_size >= 128 ? __bank0_fixed_size : 0;
  __bank6_fixed_size = __cart_rom_size >= 128 ? __bank0_fixed_size : 0;
  __bank7_fixed_size = __cart_rom_size >= 128 ? __bank0_fixed_size : 0;

  __bank8_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank9_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank10_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank11_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank12_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank13_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank14_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;
  __bank15_fixed_size = __cart_rom_size >= 256 ? __bank0_fixed_size : 0;

  __bank16_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank17_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank18_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank19_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank20_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank21_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank22_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank23_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank24_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank25_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank26_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank27_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank28_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank29_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank30_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;
  __bank31_fixed_size = __cart_rom_size >= 512 ? __bank0_fixed_size : 0;

  .bank0 __bank0_lma + __bank0_fixed_size : {
    *(.bank0 .bank0.*)
  } >bank0

  .bank1 __bank1_lma + __bank1_fixed_size : {
    *(.bank1 .bank1.*)
  } >bank1

  .bank2 __bank2_lma + __bank2_fixed_size : {
    *(.bank2 .bank2.*)
  } >bank2

  .bank3 __bank3_lma + __bank3_fixed_size : {
    *(.bank3 .bank3.*)
  } >bank3

  .bank4 __bank4_lma + __bank4_fixed_size : {
    *(.bank4 .bank4.*)
  } >bank4

  .bank5 __bank5_lma + __bank5_fixed_size : {
    *(.bank5 .bank5.*)
  } >bank5

  .bank6 __bank6_lma + __bank6_fixed_size : {
    *(.bank6 .bank6.*)
  } >bank6

  .bank7 __bank7_lma + __bank7_fixed_size : {
    *(.bank7 .bank7.*)
  } >bank7

  .bank8 __bank8_lma + __bank8_fixed_size : {
    *(.bank8 .bank8.*)
  } >bank8

  .bank9 __bank9_lma + __bank9_fixed_size : {
    *(.bank9 .bank9.*)
  } >bank9

  .bank10 __bank10_lma + __bank10_fixed_size : {
    *(.bank10 .bank10.*)
  } >bank10

  .bank11 __bank11_lma + __bank11_fixed_size : {
    *(.bank11 .bank11.*)
  } >bank11

  .bank12 __bank12_lma + __bank12_fixed_size : {
    *(.bank12 .bank12.*)
  } >bank12

  .bank13 __bank13_lma + __bank13_fixed_size : {
    *(.bank13 .bank13.*)
  } >bank13

  .bank14 __bank14_lma + __bank14_fixed_size : {
    *(.bank14 .bank14.*)
  } >bank14

  .bank15 __bank15_lma + __bank15_fixed_size : {
    *(.bank15 .bank15.*)
  } >bank15

  .bank16 __bank16_lma + __bank16_fixed_size : {
    *(.bank16 .bank16.*)
  } >bank16

  .bank17 __bank17_lma + __bank17_fixed_size : {
    *(.bank17 .bank17.*)
  } >bank17

  .bank18 __bank18_lma + __bank17_fixed_size : {
    *(.bank18 .bank18.*)
  } >bank18

  .bank19 __bank19_lma + __bank19_fixed_size : {
    *(.bank19 .bank19.*)
  } >bank19

  .bank20 __bank20_lma + __bank20_fixed_size : {
    *(.bank20 .bank20.*)
  } >bank20

  .bank21 __bank21_lma + __bank21_fixed_size : {
    *(.bank21 .bank21.*)
  } >bank21

  .bank22 __bank22_lma + __bank22_fixed_size : {
    *(.bank22 .bank22.*)
  } >bank22

  .bank23 __bank23_lma + __bank23_fixed_size : {
    *(.bank23 .bank23.*)
  } >bank23

  .bank24 __bank24_lma + __bank24_fixed_size : {
    *(.bank24 .bank24.*)
  } >bank24

  .bank25 __bank25_lma + __bank25_fixed_size : {
    *(.bank25 .bank25.*)
  } >bank25

  .bank26 __bank26_lma + __bank26_fixed_size : {
    *(.bank26 .bank26.*)
  } >bank26

  .bank27 __bank27_lma + __bank27_fixed_size : {
    *(.bank27 .bank27.*)
  } >bank27

  .bank28 __bank28_lma + __bank28_fixed_size : {
    *(.bank28 .bank28.*)
  } >bank28

  .bank29 __bank29_lma + __bank29_fixed_size : {
    *(.bank29 .bank29.*)
  } >bank29

  .bank30 __bank30_lma + __bank30_fixed_size : {
    *(.bank30 .bank30.*)
  } >bank30

  .bank31 __bank31_lma + __bank31_fixed_size : {
    *(.bank31 .bank31.*)
  } >bank31

  .bank0     : { *(.bank0     .bank0.*)     } >bank0
  .tail0     : { KEEP(*(.tail0))            } >tail0
  .bank1     : { *(.bank1     .bank1.*)     } >bank1
  .bank2     : { *(.bank2     .bank2.*)     } >bank2
  .bank3     : { *(.bank3     .bank3.*)     } >bank3
  .bank4     : { *(.bank4     .bank4.*)     } >bank4
  .bank5     : { *(.bank5     .bank5.*)     } >bank5
  .bank6     : { *(.bank6     .bank6.*)     } >bank6
  .bank7     : { *(.bank7     .bank7.*)     } >bank7
  .bank8     : { *(.bank8     .bank8.*)     } >bank8
  .bank9     : { *(.bank9     .bank9.*)     } >bank9
  .bank10    : { *(.bank10    .bank10.*)    } >bank10
  .bank11    : { *(.bank11    .bank11.*)    } >bank11
  .bank12    : { *(.bank12    .bank12.*)    } >bank12
  .bank13    : { *(.bank13    .bank13.*)    } >bank13
  .bank14    : { *(.bank14    .bank14.*)    } >bank14
  .bank15    : { *(.bank15    .bank15.*)    } >bank15
  .bank16    : { *(.bank16    .bank16.*)    } >bank16
  .bank17    : { *(.bank17    .bank17.*)    } >bank17
  .bank18    : { *(.bank18    .bank18.*)    } >bank18
  .bank19    : { *(.bank19    .bank19.*)    } >bank19
  .bank20    : { *(.bank20    .bank20.*)    } >bank20
  .bank21    : { *(.bank21    .bank21.*)    } >bank21
  .bank22    : { *(.bank22    .bank22.*)    } >bank22
  .bank23    : { *(.bank23    .bank23.*)    } >bank23
  .bank24    : { *(.bank24    .bank24.*)    } >bank24
  .bank25    : { *(.bank25    .bank25.*)    } >bank25
  .bank26    : { *(.bank26    .bank26.*)    } >bank26
  .bank27    : { *(.bank27    .bank27.*)    } >bank27
  .bank28    : { *(.bank28    .bank28.*)    } >bank28
  .bank29    : { *(.bank29    .bank29.*)    } >bank29
  .bank30    : { *(.bank30    .bank30.*)    } >bank30
  .bank31    : { *(.bank31    .bank31.*)    } >bank31

}

/* Each bank has a copy of the fixed section from bank0, bank0 has a
 * tail for the cartridge metadata */
OUTPUT_FORMAT {
  FULL(bank0, 0, __bank0_fixed_size) FULL(bank0, __bank0_fixed_size)   FULL(tail0)

  FULL(bank0, 0, __bank1_fixed_size) FULL(bank1, __bank1_fixed_size)

  FULL(bank0, 0, __bank2_fixed_size) FULL(bank2, __bank2_fixed_size)
  FULL(bank0, 0, __bank3_fixed_size) FULL(bank3, __bank3_fixed_size)

  FULL(bank0, 0, __bank4_fixed_size) FULL(bank4, __bank4_fixed_size)
  FULL(bank0, 0, __bank5_fixed_size) FULL(bank5, __bank5_fixed_size)
  FULL(bank0, 0, __bank6_fixed_size) FULL(bank6, __bank6_fixed_size)
  FULL(bank0, 0, __bank7_fixed_size) FULL(bank7, __bank7_fixed_size)

  FULL(bank0, 0, __bank8_fixed_size) FULL(bank8, __bank8_fixed_size)
  FULL(bank0, 0, __bank9_fixed_size) FULL(bank9, __bank9_fixed_size)
  FULL(bank0, 0, __bank10_fixed_size) FULL(bank10, __bank10_fixed_size)
  FULL(bank0, 0, __bank11_fixed_size) FULL(bank11, __bank11_fixed_size)
  FULL(bank0, 0, __bank12_fixed_size) FULL(bank12, __bank12_fixed_size)
  FULL(bank0, 0, __bank13_fixed_size) FULL(bank13, __bank13_fixed_size)
  FULL(bank0, 0, __bank14_fixed_size) FULL(bank14, __bank14_fixed_size)
  FULL(bank0, 0, __bank15_fixed_size) FULL(bank15, __bank15_fixed_size)

  FULL(bank0, 0, __bank16_fixed_size) FULL(bank16, __bank16_fixed_size)
  FULL(bank0, 0, __bank17_fixed_size) FULL(bank17, __bank17_fixed_size)
  FULL(bank0, 0, __bank18_fixed_size) FULL(bank18, __bank18_fixed_size)
  FULL(bank0, 0, __bank19_fixed_size) FULL(bank19, __bank19_fixed_size)
  FULL(bank0, 0, __bank20_fixed_size) FULL(bank20, __bank20_fixed_size)
  FULL(bank0, 0, __bank21_fixed_size) FULL(bank21, __bank21_fixed_size)
  FULL(bank0, 0, __bank22_fixed_size) FULL(bank22, __bank22_fixed_size)
  FULL(bank0, 0, __bank23_fixed_size) FULL(bank23, __bank23_fixed_size)
  FULL(bank0, 0, __bank24_fixed_size) FULL(bank24, __bank24_fixed_size)
  FULL(bank0, 0, __bank25_fixed_size) FULL(bank25, __bank25_fixed_size)
  FULL(bank0, 0, __bank26_fixed_size) FULL(bank26, __bank26_fixed_size)
  FULL(bank0, 0, __bank27_fixed_size) FULL(bank27, __bank27_fixed_size)
  FULL(bank0, 0, __bank28_fixed_size) FULL(bank28, __bank28_fixed_size)
  FULL(bank0, 0, __bank29_fixed_size) FULL(bank29, __bank29_fixed_size)
  FULL(bank0, 0, __bank30_fixed_size) FULL(bank30, __bank30_fixed_size)
  FULL(bank0, 0, __bank31_fixed_size) FULL(bank31, __bank31_fixed_size)
}
