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

/* Default cartridge size */
PROVIDE(__cart_rom_size = 128);

ASSERT(__cart_rom_size == 1 << LOG2CEIL(__cart_rom_size),
       "ATARI 800 MegaCart cartridge: __cart_rom_size size must be a power of 2.")
ASSERT(__cart_rom_size >= 16,
       "ATARI 800 MegaCart cartridge: __cart_rom_size size must be >= 16 KiB.")
ASSERT(__cart_rom_size <= 512,
       "ATARI 800 MegaCart cartridge: __cart_rom_size size must be <= 512 KiB.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* Memory as low as 0x700 works when not using DOS.  Assume we have
     at most 16 KiB of RAM to maximize compatabilty with the Atari 400
     and Atari 600XL models. */
  ram (w) : ORIGIN = 0x700, LENGTH = 0x4000 - 0x700
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
  tail0        : ORIGIN = __bank0_lma + 0x4000 - 20, LENGTH = 20

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

OUTPUT_FORMAT {
  FULL(bank0)
  FULL(tail0)
  FULL(bank1)
  FULL(bank2)
  FULL(bank3)
  FULL(bank4)
  FULL(bank5)
  FULL(bank6)
  FULL(bank7)
  FULL(bank8)
  FULL(bank9)
  FULL(bank10)
  FULL(bank11)
  FULL(bank12)
  FULL(bank13)
  FULL(bank14)
  FULL(bank15)
  FULL(bank16)
  FULL(bank17)
  FULL(bank18)
  FULL(bank19)
  FULL(bank20)
  FULL(bank21)
  FULL(bank22)
  FULL(bank23)
  FULL(bank24)
  FULL(bank25)
  FULL(bank26)
  FULL(bank27)
  FULL(bank28)
  FULL(bank29)
  FULL(bank30)
  FULL(bank31)
}
