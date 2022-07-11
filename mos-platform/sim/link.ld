/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x0200, LENGTH = 0xfdf0
}

SECTIONS { INCLUDE c.ld }

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xFFF0;

OUTPUT_FORMAT {
    SHORT(0x0200)
    SHORT(__data_end - 0x0200)
    TRIM(ram)

    SHORT(0xFFFA)
    SHORT(6)
    SHORT(0)
    SHORT(_start)
    SHORT(0)
}
