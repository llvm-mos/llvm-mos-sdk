/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    .fill : { . = 0x200; }
    INCLUDE c_sections.ld
    .vectors 0xFFFA : { SHORT(0) SHORT(_start) SHORT(0) }
}

/* Provide 256 imaginary (zero page) registers. */
INCLUDE imag_reg/255.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc255 == 0x00ff, "Inconsistent zero page map.")

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xFFF0;
