/* Atari 8-bit XEX file linker script.
 */

/* Provide 16 imaginary (zero page) registers located in 0xcb - 0xea range. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x2000, LENGTH = 0xa000
}

SECTIONS { INCLUDE c.ld }

OUTPUT_FORMAT {
    /* XEX magic number. */
    SHORT(0xffff)
    /* First byte of Run vector. */
    SHORT(0x02e0)
    /* Last byte of Run vector. */
    SHORT(0x02e1)
    /* Segment to be loaded to Run vector. */
    SHORT(_start)
    /* Address where first byte of main segment should be loaded. */
    SHORT(0x2000)
    /* Address of last byte of main segment.
       -- is a hack to force the early evalutation of __data_end; otherwise the
       -1 offset may be interpreted as requesting the end of the containing
       section. */
    SHORT(--__data_end - 1)

    TRIM(ram)
}
