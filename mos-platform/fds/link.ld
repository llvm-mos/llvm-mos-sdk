/* FDS executable linker script. */

/* Provide imaginary (zero page) registers in the BIOS area. */
__rc0 = 0x10;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x2f, "Inconsistent zero page map.")

INPUT(reset.o)

MEMORY {
  /* The FDS BIOS uses 16 bytes at the beginning and 15 bytes at the end - 31 bytes total - of the zero page. */
  zp : ORIGIN = __rc31 + 1, LENGTH = (0x100 - 15) - (__rc31 + 1)

  /* CPU address space. */
  ram : ORIGIN = 0x0200, LENGTH = 0x0600

  /* PRG-RAM. The last 10 bytes are reserved for the IRQ/NMI vectors. */
  prg_ram : ORIGIN = 0x6000, LENGTH = (32 * 1024) - 10
}

SECTIONS {
  .text : {
    INCLUDE text-sections.ld

    /* BIOS IRQ/NMI handlers. See irq.s for more info. */
    KEEP(*(.irq_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.irq.* .irq)))
    KEEP(*(.irq_end))

    KEEP(*(.nmi_user_1_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.nmi_user_1.* .nmi_user_1)))
    KEEP(*(.nmi_user_1_end))

    KEEP(*(.nmi_user_2_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.nmi_user_2.* .nmi_user_2)))
    KEEP(*(.nmi_user_2_end))

    KEEP(*(.nmi_user_3_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.nmi_user_3.* .nmi_user_3)))
    KEEP(*(.nmi_user_3_end))
  } >c_readonly
  INCLUDE rodata.ld
  /* A naturally page-aligned place (0x200) to place noinit buffers with high
   * alignment requirement (e.g. OAM) */
  .aligned (NOLOAD) : { *(.aligned .aligned.*) } >ram
  INCLUDE data.ld
  INCLUDE zp.ld
  INCLUDE bss.ld
  INCLUDE noinit.ld

  .ram (NOLOAD) : { *(.ram .ram.*) } > ram
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram

  .vectors (INFO) : {
    SHORT(nmi_user_1)
    SHORT(nmi_user_2)
    SHORT(bypass)
    SHORT(_start)
    SHORT(irq)
  }
}

REGION_ALIAS("c_readonly", prg_ram)
REGION_ALIAS("c_writeable", prg_ram)

__stack = ORIGIN(prg_ram) + LENGTH(prg_ram) - 1;

OUTPUT_FORMAT {
  TRIM(prg_ram)
}
