/* C64 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

OUTPUT_FORMAT(binary)

INPUT(basic_header.o)

SECTIONS {
    /* Tells the C64 LOAD command where to place the file's contents. */
    .prg_header 0x0801 - 2 : { SHORT(0x0801) }

    /* BASIC program that jumps to _start = 2061. */
    .basic_header : { *(.basic_header) }

    INCLUDE c_sections.ld
}

ASSERT(ADDR(.basic_header) == 0x0801, "BASIC header at incorrect address.")
ASSERT(_start == 2061, "_start began at different address than BASIC header expects.")

/* Provide 142 imaginary (zero page) registers (the BASIC area from $02 to $8f) */
PROVIDE(__rc0 = 0x0002);
INCLUDE imag_reg/141.ld
ASSERT(__rc0 == 0x0002, "Inconsistent zero page map.")
ASSERT(__rc141 == 0x008f, "Inconsistent zero page map.")

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0x9FFF;
