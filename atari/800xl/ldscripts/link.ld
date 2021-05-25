/* Atari800XL XEX file linker script.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    /* XEX header */
    .prg_header 0x2000 - 6 : {SHORT(0xffff), SHORT(0x2000), SHORT(0x2000 + ADDR(.bss) - ADDR(.header) - 1), }

    .header : { *(.prg_header) }

    .text : { *(.start) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }
    .bss (NOLOAD) : { *(.bss .bss.* COMMON) }
    .noinit (NOLOAD) : { *(.noinit .noinit.*) }
}

/* Provide 128 imaginary (zero page) registers located in 0x80 - 0xff range.
   Atari OS uses first 128 bytes (0x00 - 0x7f) of zero page itself.
   Remaining locations are intended for use by user program, but remember that
   Basic and Floating Point routines also use this part of zero page.
*/

PROVIDE(__rc0 = 0x80);
INCLUDE imag_reg/127.ld
ASSERT(__rc0 == 0x0080, "Inconsistent zero page map.")
ASSERT(__rc127 == 0x00ff, "Inconsistent zero page map.")

ASSERT(ADDR(.header) == 0x2000, "header at incorrect address.")
ASSERT(_start == 0x2000, "_start began at different address than expected.")

/* Set initial soft stack address (It grows down.) */
__stack = 0x1FFF;
