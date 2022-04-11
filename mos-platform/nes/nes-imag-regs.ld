/* Provide imaginary (zero page) registers. */
PROVIDE(__rc0 = 0x0000);
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")
