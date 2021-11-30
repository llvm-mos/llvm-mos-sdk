/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    .load_block_header 0x200 - 4 : {
        SHORT(__load_begin)
        SHORT(__load_end - __load_begin)
    }

    __load_begin = .;
    .text : { *(.start) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }
    __load_end = .;

    .vector_block_header : {
        SHORT(0xFFFA)
        SHORT(6)
    }

    .vector_block : {
        SHORT(0)
        SHORT(_start)
        SHORT(0)
    }

    __bss_begin = .;
    .bss (NOLOAD) : { *(.bss .bss.* COMMON) }
    __bss_end = .;
    .noinit (NOLOAD) : { *(.noinit .noinit.*) }
}

/* Provide 256 imaginary (zero page) registers. */
INCLUDE imag_reg/255.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc255 == 0x00ff, "Inconsistent zero page map.")

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xFFF0;
