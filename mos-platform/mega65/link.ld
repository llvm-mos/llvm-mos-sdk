/* MEGA65 PRG file linker script.
 *
 * C64 BASIC memory regions are freely overwritten up until $E000
 * (the basic header switches to bank 0, i.e. C64 layout)
 *
 * Produces a PRG file with a SYS command to start the program.
 */

MEMORY {
    ram (rw) : ORIGIN = 0x2001, LENGTH = 0xbfff
}

INPUT(basic-header.o)

SECTIONS {
    /* BASIC program that jumps to _start. */
    .basic_header : { *(.basic_header) }

    INCLUDE c.ld
}

/* Provide imaginary (zero page) registers in the BASIC area. */
__rc0 = 0x0002;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x0002, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x0021, "Inconsistent zero page map.")

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0xdfff;

OUTPUT_FORMAT {
    /* Tells the MEGA65 LOAD command where to place the file's contents. */
    SHORT(0x2001)
    TRIM(ram)
}
