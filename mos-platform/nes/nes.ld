/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* CPU address space. */
  ram (w) : ORIGIN = 0x0200, LENGTH = 0x0600
}
