/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

MEMORY {
    ram (rw) : ORIGIN = 0x0200, LENGTH = 0xfdf0
}

SECTIONS {
    INCLUDE c.ld
}

/* Provide imaginary (zero page) registers. */
PROVIDE(__rc0 = 0x0000);
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

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
