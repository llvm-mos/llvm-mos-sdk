/* Atari 5200 linker script.

  32 KiB banks, 1 bank would be a normal 32 KiB cartridge, 128 KiB
  through 512 KiB would be a Super Cart.

  We have a common "fixed" region that is a prefix for all banks.  The
  last bank has a tail used to initialize the ROM.

  https://github.com/atari800/atari800/blob/ATARI800_5_0_0/DOC/cart.txt
*/

PROVIDE(__cart_rom_size = 512);

ASSERT(__cart_rom_size == 1 << LOG2CEIL(__cart_rom_size),
       "ATARI 5200: __cart_rom_size size must be a power of 2.")
ASSERT(__cart_rom_size >= 32,
       "ATARI 5200: __cart_rom_size size must be >= 32 KiB.")
ASSERT(__cart_rom_size <= 512,
       "ATARI 5200: __cart_rom_size size must be <= 512 KiB.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* Memory from 0x300 to 0x3c00 is usable in this current
     implementation. */
  ram (w) : ORIGIN = 0x300, LENGTH = 0x3c00 - 0x300
}

/* Provide imaginary (zero page) registers. */
/* TODO; we have more space available here, see the .cfg file. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

/* LMAs */
__fixed_lma     = 0x00004000;

__bank0_lma     = 0x01004000;
__bank1_lma     = 0x01014000;
__bank2_lma     = 0x01024000;
__bank3_lma     = 0x01034000;
__bank4_lma     = 0x01044000;
__bank5_lma     = 0x01054000;
__bank6_lma     = 0x01064000;
__bank7_lma     = 0x01074000;
__bank8_lma     = 0x01084000;
__bank9_lma     = 0x01094000;
__bank10_lma    = 0x010a4000;
__bank11_lma    = 0x010b4000;
__bank12_lma    = 0x010c4000;
__bank13_lma    = 0x010d4000;
__bank14_lma    = 0x010e4000;
__bank15_lma    = 0x010f4000;

__tail_lma      = 0x0000bfc0;

MEMORY {
  /* shared across all banks */
  fixed		: ORIGIN = __fixed_lma,  LENGTH = 0x8000

  /* the last bank has to be shrunk to make room for the tail */
  bank0         : ORIGIN = __bank0_lma,  LENGTH = __cart_rom_size  == 32 ? 0x8000 - 64 : 0x8000

  bank1         : ORIGIN = __bank1_lma,  LENGTH = __cart_rom_size >=  64 ? (__cart_rom_size ==  64 ? 0x8000 - 64 : 0x8000 ) : 0
  bank2         : ORIGIN = __bank2_lma,  LENGTH = __cart_rom_size >= 128 ? 0x8000 : 0
  bank3         : ORIGIN = __bank3_lma,  LENGTH = __cart_rom_size >= 128 ? (__cart_rom_size == 128 ? 0x8000 - 64 : 0x8000 ) : 0
  bank4         : ORIGIN = __bank4_lma,  LENGTH = __cart_rom_size >= 256 ? 0x8000 : 0
  bank5         : ORIGIN = __bank5_lma,  LENGTH = __cart_rom_size >= 256 ? 0x8000 : 0
  bank6         : ORIGIN = __bank6_lma,  LENGTH = __cart_rom_size >= 256 ? 0x8000 : 0
  bank7         : ORIGIN = __bank7_lma,  LENGTH = __cart_rom_size >= 256 ? (__cart_rom_size == 256 ? 0x8000 - 64 : 0x8000 ) : 0

  bank8         : ORIGIN = __bank8_lma,  LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank9         : ORIGIN = __bank9_lma,  LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank10        : ORIGIN = __bank10_lma, LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank11        : ORIGIN = __bank11_lma, LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank12        : ORIGIN = __bank12_lma, LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank13        : ORIGIN = __bank13_lma, LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank14        : ORIGIN = __bank14_lma, LENGTH = __cart_rom_size >= 512 ? 0x8000 : 0
  bank15        : ORIGIN = __bank15_lma, LENGTH = __cart_rom_size >= 512 ? (__cart_rom_size == 512 ? 0x8000 - 64 : 0x8000 ) : 0

  /* the tail is put at the end of the last bank, it has the cartridge
     metadata but also needs to "reserve" some space for
     bank-switch-reads. */
  tail          : ORIGIN = __tail_lma,   LENGTH = 0x40
}

REGION_ALIAS("c_writeable", ram)
REGION_ALIAS("c_readonly", fixed)

SECTIONS {
  INCLUDE c.ld

  /* Fixed region, included as a prefix in all banks */
  .fixed : {
    *(.fixed .fixed.*)
    __fixed_end = .;
    __fixed_size = __fixed_end - __fixed_lma;
  } >fixed

  /* Offset other banks. */
  __bank0_fixed_size =  __cart_rom_size >=  32 ? __fixed_size : 0;

  __bank1_fixed_size =  __cart_rom_size >=  64 ? __fixed_size : 0;

  __bank2_fixed_size =  __cart_rom_size >= 128 ? __fixed_size : 0;
  __bank3_fixed_size =  __cart_rom_size >= 128 ? __fixed_size : 0;

  __bank4_fixed_size =  __cart_rom_size >= 256 ? __fixed_size : 0;
  __bank5_fixed_size =  __cart_rom_size >= 256 ? __fixed_size : 0;
  __bank6_fixed_size =  __cart_rom_size >= 256 ? __fixed_size : 0;
  __bank7_fixed_size =  __cart_rom_size >= 256 ? __fixed_size : 0;

  __bank8_fixed_size =  __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank9_fixed_size =  __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank10_fixed_size = __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank11_fixed_size = __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank12_fixed_size = __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank13_fixed_size = __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank14_fixed_size = __cart_rom_size >= 512 ? __fixed_size : 0;
  __bank15_fixed_size = __cart_rom_size >= 512 ? __fixed_size : 0;

  .bank0 __bank0_lma + __fixed_size : {
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

  .fixed     : { *(.fixed     .fixed.*)     } >fixed

  .bank0     : { *(.bank0     .bank0.*)     } >bank0
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


  /* Tail: 64 bytes in total

     bank-switch-read-addresses, 16 bytes; from the platform PoV there
     are from 0xbfc0 through 0xbfcf

     ... 24 unused bytes ...

     Cartridge Metadata: 24 bytes

     20 bytes of title at bfe8 (ATASCII)
     2 year 19xx at bffc - if bffd is 0xff this means diag cart - TODO
     init at bffe

     TODO: We might want to juse use things in diag cart mode (some
     games do this) and ignore the above.  */
  .vector __tail_lma + (64 - 24) : {
    BYTE(0x40) // space
    BYTE(0x2c) // "llvm-mos" (shifted to lower 32 where colors rotate)
    BYTE(0x2c)
    BYTE(0x36)
    BYTE(0x2d)
    BYTE(0x0d)
    BYTE(0x2d)
    BYTE(0x2f)
    BYTE(0x33)
    BYTE(0x40) // space
    BYTE(0x63) // "compiled" (shifted to 3rd 32 where it's white)
    BYTE(0x6f)
    BYTE(0x6d)
    BYTE(0x70)
    BYTE(0x69)
    BYTE(0x6c)
    BYTE(0x65)
    BYTE(0x64)
    BYTE(0x40) // space
    BYTE(0x40) // space

    /* year in 19xx, y2k problem issue so pick something, the internet
       says this was the best year in the 1900s.  Moon landing! */
    BYTE(0x56)
    BYTE(0x59)

    SHORT(_start)
  } >tail
}

/* All bank gets the fixed section prefix. */
OUTPUT_FORMAT {
  FULL(fixed, 0, __bank0_fixed_size)  FULL(bank0,  __bank0_fixed_size)

  FULL(fixed, 0, __bank1_fixed_size)  FULL(bank1,  __bank1_fixed_size)

  FULL(fixed, 0, __bank2_fixed_size)  FULL(bank2,  __bank2_fixed_size)
  FULL(fixed, 0, __bank3_fixed_size)  FULL(bank3,  __bank3_fixed_size)

  FULL(fixed, 0, __bank4_fixed_size)  FULL(bank4,  __bank4_fixed_size)
  FULL(fixed, 0, __bank5_fixed_size)  FULL(bank5,  __bank5_fixed_size)
  FULL(fixed, 0, __bank6_fixed_size)  FULL(bank6,  __bank6_fixed_size)
  FULL(fixed, 0, __bank7_fixed_size)  FULL(bank7,  __bank7_fixed_size)

  FULL(fixed, 0, __bank8_fixed_size)  FULL(bank8,  __bank8_fixed_size)
  FULL(fixed, 0, __bank9_fixed_size)  FULL(bank9,  __bank9_fixed_size)
  FULL(fixed, 0, __bank10_fixed_size) FULL(bank10, __bank10_fixed_size)
  FULL(fixed, 0, __bank11_fixed_size) FULL(bank11, __bank11_fixed_size)
  FULL(fixed, 0, __bank12_fixed_size) FULL(bank12, __bank12_fixed_size)
  FULL(fixed, 0, __bank13_fixed_size) FULL(bank13, __bank13_fixed_size)
  FULL(fixed, 0, __bank14_fixed_size) FULL(bank14, __bank14_fixed_size)
  FULL(fixed, 0, __bank15_fixed_size) FULL(bank15, __bank15_fixed_size)

  FULL(tail)
}
