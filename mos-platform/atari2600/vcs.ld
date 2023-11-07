
MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  pia_ram (w) : ORIGIN = 0x80, LENGTH = 0x80
}

/* Provide imaginary (zero page) registers. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

REGION_ALIAS("c_writeable", pia_ram)

