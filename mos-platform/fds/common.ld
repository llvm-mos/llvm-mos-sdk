/* FDS executable linker script. */

__prg_ram_size = 32;

/* Provide imaginary (zero page) registers in the BIOS area. */
__rc0 = 0x10;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x2f, "Inconsistent zero page map.")

MEMORY {
  /* The FDS BIOS uses 16 bytes at the beginning and 15 bytes at the end - 31 bytes total - of the zero page. */
  zp : ORIGIN = __rc31 + 1, LENGTH = 0xE1 - (__rc31 + 1)

  /* CPU address space. */
  ram : ORIGIN = 0x0200, LENGTH = 0x0600
}

SECTIONS {
  .text : {
       INCLUDE text-sections.ld

       KEEP(*(.irq_begin))
       KEEP(*(SORT_BY_INIT_PRIORITY(.irq.* .irq)))
       KEEP(*(.irq_end))

       KEEP(*(.nmi_begin))
       KEEP(*(SORT_BY_INIT_PRIORITY(.nmi.* .nmi)))
       KEEP(*(.nmi_end))

       KEEP(*(.nmi_2_begin))
       KEEP(*(SORT_BY_INIT_PRIORITY(.nmi_2.* .nmi_2)))
       KEEP(*(.nmi_2_end))

       KEEP(*(.nmi_3_begin))
       KEEP(*(SORT_BY_INIT_PRIORITY(.nmi_3.* .nmi_3)))
       KEEP(*(.nmi_3_end))
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

  .vectors (COPY) : { KEEP(*(.vectors)) }
}
