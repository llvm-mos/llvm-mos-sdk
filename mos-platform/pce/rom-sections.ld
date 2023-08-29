SECTIONS {
  .text : {
    INCLUDE text-sections.ld

    KEEP(*(.irq_timer_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.irq_timer.* .irq_timer)))
    KEEP(*(.irq_timer_end))

    KEEP(*(.irq_vdc_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.irq_vdc.* .irq_vdc)))
    KEEP(*(.irq_vdc_end))

    KEEP(*(.irq_ext_begin))
    KEEP(*(SORT_BY_INIT_PRIORITY(.irq_ext.* .irq_ext)))
    KEEP(*(.irq_ext_end))
  } >c_readonly
  INCLUDE rodata.ld
  INCLUDE data.ld
  INCLUDE zp.ld
  INCLUDE bss.ld
  INCLUDE noinit.ld

  /* Used by zero-bss routines. */
  HIDDEN(__zero_bss_start = __bss_start + 1);
  HIDDEN(__zero_bss_size = __bss_size >= 2 ? __bss_size - 1 : 1);
  HIDDEN(__zero_zp_bss_start = __zp_bss_start + 1);
  HIDDEN(__zero_zp_bss_size = __zp_bss_size >= 2 ? __zp_bss_size - 1 : 1);
}
