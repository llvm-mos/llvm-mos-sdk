/* C64 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    /* Tells the C64 LOAD command where to place the file's contents. */
    .prg_header 0x1000 - 6 : {SHORT(0xffff), SHORT(0x1000), SHORT(0x1000 + ADDR(.bss) - ADDR(.basic_header) - 1), }

    /* BASIC program that jumps to _start = 2061. */
    .basic_header : { *(.prg_header) }

    .text : { *(.start) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }
    .bss (NOLOAD) : { *(.bss .bss.* COMMON) }
    .noinit (NOLOAD) : { *(.noinit .noinit.*) }
}

/* Provide 128 imaginary (zero page) registers (the BASIC area from $80 to $ff) */
PROVIDE(__rc0 = 0x80);
INCLUDE imag_reg/141.ld
ASSERT(__rc0 == 0x0080, "Inconsistent zero page map.")
ASSERT(__rc127 == 0x00ff, "Inconsistent zero page map.")

ASSERT(ADDR(.basic_header) == 0x1000, "BASIC header at incorrect address.")
ASSERT(_start == 0x1000, "_start began at different address than BASIC header expects.")

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0x0FFF;
