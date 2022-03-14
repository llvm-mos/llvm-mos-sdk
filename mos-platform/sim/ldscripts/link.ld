/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    .load_block_header 0x200 - 4 : {
        SHORT(__load_start)
        SHORT(__load_end - __load_start)
    }

    __load_start = .;
    INCLUDE ro_sections.ld
    INCLUDE rw_sections.ld
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

    INCLUDE noalloc_sections.ld
    __heap_start = .;
}

/* Provide imaginary (zero page) registers. */
PROVIDE(__rc0 = 0x0000);
INCLUDE imag_regs.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xFFF0;
