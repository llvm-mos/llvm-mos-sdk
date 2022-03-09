/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

MEMORY {
  ram (rw) : ORIGIN = 0x0200, LENGTH = 0xfdf0
  vectors  : ORIGIN = 0xfffa, LENGTH = 6
}

SECTIONS {
    .load_block_header (INFO) : {
        SHORT(0x200)
        SHORT(__load_end - 0x200)
    }
    INCLUDE c_sections.ld

    .vectors_header (INFO) : {
        SHORT(0xfffa)
        SHORT(6)
    }
    .vectors : {
        SHORT(0)
        SHORT(_start)
        SHORT(0)
    } >vectors
}

/* Provide imaginary (zero page) registers. */
PROVIDE(__rc0 = 0x0000);
INCLUDE imag_regs.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xFFF0;
