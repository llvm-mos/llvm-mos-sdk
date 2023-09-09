/* Linker script for Ben Eater's 6502 breadboard computer. */

/* Provide imaginary (zero page) registers. */
__rc0 = 0xe0;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0xff, "Inconsistent zero page map.")

MEMORY {
  zp : ORIGIN = 0x00, LENGTH = 0xe0
  ram : ORIGIN = 0x200, LENGTH = 0x4000 - 0x200
  rom : ORIGIN = 0x8000, LENGTH = 0x7ffa
}

/* Provide default IRQ and NMI handlers if the program doesn't have them. */
PROVIDE(irq = _irq_default);
PROVIDE(nmi = _irq_default);

REGION_ALIAS("c_readonly", rom)
REGION_ALIAS("c_writeable", ram)

SECTIONS { INCLUDE c.ld }

/* Set initial soft stack address to just above last ram address. (It grows down.) */
__stack = ORIGIN(ram) + LENGTH(ram);

OUTPUT_FORMAT {
  FULL(rom)
  SHORT(nmi)
  SHORT(_start)
  SHORT(_irqbrk)
}
