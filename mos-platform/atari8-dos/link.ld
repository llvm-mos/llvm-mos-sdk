/* Atari 8-bit DOS / .XEX file linker script. */

/* Provide 16 imaginary (zero page) registers located in 0xcb - 0xea range. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

/*
Target compatability with ATARI DOS 2.0 and newer, as well as later
version of SpartaDOS.

ATARI DOS 1.0 (1979) puts MEMLO at 0x2A08.
ATARI DOS 2.0D (1980) puts MEMLO at 0x1DFC.
ATARI DOS 2.0S (1980), 2.5 (1984), XE 1.0 (1988) all put MEMLO at 0x1CFC.
SpartaDOS 1.1 HS (1984) puts MEMLO at 0x2557.
SpartaDOS X 4.2 (1988) puts MEMLO at 0x1B2D.
SpartaDOS X 4.49 (2020) puts MEMLO at 0x1DBA.
*/
MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x2000, LENGTH = 0xa000
}

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

SECTIONS { INCLUDE c.ld }

OUTPUT_FORMAT {
    SHORT(0xffff)    /* XEX magic number. */
    SHORT(0x02e0)    /* First byte of Run vector. */
    SHORT(0x02e1)    /* Last byte of Run vector. */
    SHORT(_start)    /* Segment to be loaded to Run vector. */
    SHORT(0x2000)    /* Address where first byte of main segment should be loaded. */

    /* Address of last byte of main segment.
       -- is a hack to force the early evalutation of __data_end; otherwise the
       -1 offset may be interpreted as requesting the end of the containing
       section. */
    SHORT(--__data_end - 1)

    TRIM(ram)
}
