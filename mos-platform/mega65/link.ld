/* MEGA65 PRG file linker script.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

MEMORY {
    /* allocate in $2001 - $A000 range */
    ram (rw) : ORIGIN = 0x2001, LENGTH = 0x7fff
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
__stack = 0x7FFF;

OUTPUT_FORMAT {
    /* Tells the LOAD command where to place the file's contents. */
    SHORT(0x2001)
    TRIM(ram)
}
