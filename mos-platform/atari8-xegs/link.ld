/* Atari800 XEGS cartridge linker script.

  Right now we support 32, 64, 128, 256 and 512 KiB sized XEGS
  cartridges.

  There are log2(__cart_rom_size)-1 switchable banks of 8KiB size
  switchabled into 0x8000, the last bank will always be mapped. it's
  the "fixed" bank mapped at 0xa000.

   32 has banks  0..2 + fixed
   64 has banks  0..6 + fixed
  128 has banks 0..14 + fixed
  256 has banks 0..30 + fixed
  512 has banks 0..62 + fixed
*/


/* PROVIDE(__cart_rom_size = 256); */

ASSERT(__cart_rom_size == 1 << LOG2CEIL(__cart_rom_size),
       "ATARI 800 XEGS cartridge: __cart_rom_size size must be a power of 2.")
ASSERT(__cart_rom_size >= 32,
       "ATARI 800 XEGS cartridge: __cart_rom_size size must be >= 32.")
ASSERT(__cart_rom_size <= 512,
       "ATARI 800 XEGS cartridge: __cart_rom_size size must be <= 512.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
  /* Memory as low as 0x700 works when not using DOS. */
  ram (w) : ORIGIN = 0x700, LENGTH = 0x2000 - 0x700
}

/* Provide imaginary (zero page) registers. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

/* LMAs */
__fixed_lma	= 0x00a000;
__bank0_lma	= 0x008000;
__bank1_lma	= 0x018000;
__bank2_lma	= 0x028000;
__bank3_lma	= 0x038000;
__bank4_lma	= 0x048000;
__bank5_lma	= 0x058000;
__bank6_lma	= 0x068000;
__bank7_lma	= 0x078000;
__bank8_lma	= 0x088000;
__bank9_lma	= 0x098000;
__bank10_lma	= 0x0a8000;
__bank11_lma	= 0x0b8000;
__bank12_lma	= 0x0c8000;
__bank13_lma	= 0x0d8000;
__bank14_lma	= 0x0e8000;
__bank15_lma	= 0x0f8000;
__bank16_lma	= 0x108000;
__bank17_lma	= 0x118000;
__bank18_lma	= 0x128000;
__bank19_lma	= 0x138000;
__bank20_lma	= 0x148000;
__bank21_lma	= 0x158000;
__bank22_lma	= 0x168000;
__bank23_lma	= 0x178000;
__bank24_lma	= 0x188000;
__bank25_lma	= 0x198000;
__bank26_lma	= 0x1a8000;
__bank27_lma	= 0x1b8000;
__bank28_lma	= 0x1c8000;
__bank29_lma	= 0x1d8000;
__bank30_lma	= 0x1e8000;
__bank31_lma	= 0x1f8000;
__bank32_lma	= 0x208000;
__bank33_lma	= 0x218000;
__bank34_lma	= 0x228000;
__bank35_lma	= 0x238000;
__bank36_lma	= 0x248000;
__bank37_lma	= 0x258000;
__bank38_lma	= 0x268000;
__bank39_lma	= 0x278000;
__bank40_lma	= 0x288000;
__bank41_lma	= 0x298000;
__bank42_lma	= 0x2a8000;
__bank43_lma	= 0x2b8000;
__bank44_lma	= 0x2c8000;
__bank45_lma	= 0x2d8000;
__bank46_lma	= 0x2e8000;
__bank47_lma	= 0x2f8000;
__bank48_lma	= 0x308000;
__bank49_lma	= 0x318000;
__bank50_lma	= 0x328000;
__bank51_lma	= 0x338000;
__bank52_lma	= 0x348000;
__bank53_lma	= 0x358000;
__bank54_lma	= 0x368000;
__bank55_lma	= 0x378000;
__bank56_lma	= 0x388000;
__bank57_lma	= 0x398000;
__bank58_lma	= 0x3a8000;
__bank59_lma	= 0x3b8000;
__bank60_lma	= 0x3c8000;
__bank61_lma	= 0x3d8000;
__bank62_lma	= 0x3e8000;


MEMORY {
  bank0		: ORIGIN = __bank0_lma,  LENGTH = __cart_rom_size >=  32 ? 0x2000 : 0
  bank1		: ORIGIN = __bank1_lma,  LENGTH = __cart_rom_size >=  32 ? 0x2000 : 0
  bank2		: ORIGIN = __bank2_lma,  LENGTH = __cart_rom_size >=  32 ? 0x2000 : 0

  bank3		: ORIGIN = __bank3_lma,  LENGTH = __cart_rom_size >=  64 ? 0x2000 : 0
  bank4		: ORIGIN = __bank4_lma,  LENGTH = __cart_rom_size >=  64 ? 0x2000 : 0
  bank5		: ORIGIN = __bank5_lma,  LENGTH = __cart_rom_size >=  64 ? 0x2000 : 0
  bank6		: ORIGIN = __bank6_lma,  LENGTH = __cart_rom_size >=  64 ? 0x2000 : 0

  bank7		: ORIGIN = __bank7_lma,  LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank8		: ORIGIN = __bank8_lma,  LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank9		: ORIGIN = __bank9_lma,  LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank10	: ORIGIN = __bank10_lma, LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank11	: ORIGIN = __bank11_lma, LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank12	: ORIGIN = __bank12_lma, LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank13	: ORIGIN = __bank13_lma, LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0
  bank14	: ORIGIN = __bank14_lma, LENGTH = __cart_rom_size >= 128 ? 0x2000 : 0

  bank15	: ORIGIN = __bank15_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank16	: ORIGIN = __bank16_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank17	: ORIGIN = __bank17_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank18	: ORIGIN = __bank18_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank19	: ORIGIN = __bank19_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank20	: ORIGIN = __bank20_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank21	: ORIGIN = __bank21_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank22	: ORIGIN = __bank22_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank23	: ORIGIN = __bank23_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank24	: ORIGIN = __bank24_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank25	: ORIGIN = __bank25_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank26	: ORIGIN = __bank26_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank27	: ORIGIN = __bank27_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank28	: ORIGIN = __bank28_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank29	: ORIGIN = __bank29_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0
  bank30	: ORIGIN = __bank30_lma, LENGTH = __cart_rom_size >= 256 ? 0x2000 : 0

  bank31	: ORIGIN = __bank31_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank32	: ORIGIN = __bank32_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank33	: ORIGIN = __bank33_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank34	: ORIGIN = __bank34_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank35	: ORIGIN = __bank35_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank36	: ORIGIN = __bank36_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank37	: ORIGIN = __bank37_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank38	: ORIGIN = __bank38_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank39	: ORIGIN = __bank39_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank40	: ORIGIN = __bank40_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank41	: ORIGIN = __bank41_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank42	: ORIGIN = __bank42_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank43	: ORIGIN = __bank43_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank44	: ORIGIN = __bank44_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank45	: ORIGIN = __bank45_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank46	: ORIGIN = __bank46_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank47	: ORIGIN = __bank47_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank48	: ORIGIN = __bank48_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank49	: ORIGIN = __bank49_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank50	: ORIGIN = __bank50_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank51	: ORIGIN = __bank51_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank52	: ORIGIN = __bank52_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank53	: ORIGIN = __bank53_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank54	: ORIGIN = __bank54_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank55	: ORIGIN = __bank55_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank56	: ORIGIN = __bank56_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank57	: ORIGIN = __bank57_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank58	: ORIGIN = __bank58_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank59	: ORIGIN = __bank59_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank60	: ORIGIN = __bank60_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank61	: ORIGIN = __bank61_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0
  bank62	: ORIGIN = __bank62_lma, LENGTH = __cart_rom_size >= 512 ? 0x2000 : 0

  fixed		: ORIGIN = __fixed_lma,   LENGTH = 0x2000
}

REGION_ALIAS("c_writeable", ram)
REGION_ALIAS("c_readonly", fixed)

SECTIONS {
  INCLUDE c.ld

  .fixed     : { *(.fixed .fixed.*)         } >fixed

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
  .bank32    : { *(.bank32    .bank32.*)    } >bank32
  .bank33    : { *(.bank33    .bank33.*)    } >bank33
  .bank34    : { *(.bank34    .bank34.*)    } >bank34
  .bank35    : { *(.bank35    .bank35.*)    } >bank35
  .bank36    : { *(.bank36    .bank36.*)    } >bank36
  .bank37    : { *(.bank37    .bank37.*)    } >bank37
  .bank38    : { *(.bank38    .bank38.*)    } >bank38
  .bank39    : { *(.bank39    .bank39.*)    } >bank39
  .bank40    : { *(.bank40    .bank40.*)    } >bank40
  .bank41    : { *(.bank41    .bank41.*)    } >bank41
  .bank42    : { *(.bank42    .bank42.*)    } >bank42
  .bank43    : { *(.bank43    .bank43.*)    } >bank43
  .bank44    : { *(.bank44    .bank44.*)    } >bank44
  .bank45    : { *(.bank45    .bank45.*)    } >bank45
  .bank46    : { *(.bank46    .bank46.*)    } >bank46
  .bank47    : { *(.bank47    .bank47.*)    } >bank47
  .bank48    : { *(.bank48    .bank48.*)    } >bank48
  .bank49    : { *(.bank49    .bank49.*)    } >bank49
  .bank50    : { *(.bank50    .bank50.*)    } >bank50
  .bank51    : { *(.bank51    .bank51.*)    } >bank51
  .bank52    : { *(.bank52    .bank52.*)    } >bank52
  .bank53    : { *(.bank53    .bank53.*)    } >bank53
  .bank54    : { *(.bank54    .bank54.*)    } >bank54
  .bank55    : { *(.bank55    .bank55.*)    } >bank55
  .bank56    : { *(.bank56    .bank56.*)    } >bank56
  .bank57    : { *(.bank57    .bank57.*)    } >bank57
  .bank58    : { *(.bank58    .bank58.*)    } >bank58
  .bank59    : { *(.bank59    .bank59.*)    } >bank59
  .bank60    : { *(.bank60    .bank60.*)    } >bank60
  .bank61    : { *(.bank61    .bank61.*)    } >bank61
  .bank62    : { *(.bank62    .bank62.*)    } >bank62

 /* "SIZE=nnn"; used when testing linker scripts, makes hexdump useful */
 .vector 0xbff0 : {
    BYTE(0x53); BYTE(0x49); BYTE(0x5a); BYTE(0x45); BYTE(0x3d);
    BYTE(48 + __cart_rom_size / 100)
    BYTE(48 + (__cart_rom_size % 100) / 10)
    BYTE(48 + __cart_rom_size % 10)
  } >fixed

  .vector 0xbffa : {
    SHORT(_start)      /* START entrypoint (after OS setup)   */
    BYTE(0x0)          /* "Inserted"                          */
    BYTE(0x04)         /* Bits: 7=diag, 2=start, 0=Enable_DOS */
    SHORT(_cart_init)  /* INIT entrpoint (before OS setup)    */
  } >fixed
}

/* OUTPUT_FORMAT { FULL(cart_rom) } */
OUTPUT_FORMAT {
  FULL(bank0)
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
  FULL(bank32)
  FULL(bank33)
  FULL(bank34)
  FULL(bank35)
  FULL(bank36)
  FULL(bank37)
  FULL(bank38)
  FULL(bank39)
  FULL(bank40)
  FULL(bank41)
  FULL(bank42)
  FULL(bank43)
  FULL(bank44)
  FULL(bank45)
  FULL(bank46)
  FULL(bank47)
  FULL(bank48)
  FULL(bank49)
  FULL(bank50)
  FULL(bank51)
  FULL(bank52)
  FULL(bank53)
  FULL(bank54)
  FULL(bank55)
  FULL(bank56)
  FULL(bank57)
  FULL(bank58)
  FULL(bank59)
  FULL(bank60)
  FULL(bank61)
  FULL(bank62)
  FULL(fixed)
}
