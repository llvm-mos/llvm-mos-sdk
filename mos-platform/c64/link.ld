/* C64 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

MEMORY {
    ram (rw) : ORIGIN = 0x0801, LENGTH = 0x97ff
}

INPUT(basic-header.o)

SECTIONS {
    /* BASIC program that jumps to _start. */
    .basic_header : { *(.basic_header) }

    INCLUDE c.ld
}

/* Provide imaginary (zero page) registers in the BASIC area. */
PROVIDE(__rc0 = 0x0002);
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x0002, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x0021, "Inconsistent zero page map.")

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0x9FFF;

OUTPUT_FORMAT {
    /* Tells the C64 LOAD command where to place the file's contents. */
    SHORT(0x0801)
    TRIM(ram)
}
