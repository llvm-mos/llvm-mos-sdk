/* Atari800XL XEX file linker script.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    /* XEX header */
    .prg_header 0x1000 - 6 : {SHORT(0xffff), SHORT(0x1000), SHORT(0x1000 + ADDR(.bss) - ADDR(.header) - 1), }

    .header : { *(.prg_header) }

    .text : { *(.start) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }
    .bss (NOLOAD) : { *(.bss .bss.* COMMON) }
    .noinit (NOLOAD) : { *(.noinit .noinit.*) }
}

/* Provide 128 imaginary (zero page) registers (from $80 to $ff) */
PROVIDE(__rc0 = 0x80);
INCLUDE imag_reg/141.ld
ASSERT(__rc0 == 0x0080, "Inconsistent zero page map.")
ASSERT(__rc127 == 0x00ff, "Inconsistent zero page map.")

ASSERT(ADDR(.header) == 0x1000, "header at incorrect address.")
ASSERT(_start == 0x1000, "_start began at different address than expected.")

/* Set initial soft stack address (It grows down.) */
__stack = 0x0FFF;
