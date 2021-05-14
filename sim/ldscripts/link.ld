/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    .fill : { . = 0x200; }
    .text : { *(.start) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }
    .bss : { *(.bss .bss.* COMMON) }
    .noinit : { *(.noinit .noinit.*) }
    .vectors 0xFFFA : { SHORT(0) SHORT(_start) SHORT(0) }
}

/* Provide 142 imaginary (zero page) registers (the BASIC area from $02 to $8f) */
INCLUDE imag_reg/255.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc255 == 0x00ff, "Inconsistent zero page map.")

/* Set initial soft stack address to last memory address. (It grows down.) */
__stack = 0xFFF8;
