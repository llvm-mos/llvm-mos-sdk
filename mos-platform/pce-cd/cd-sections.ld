REGION_ALIAS("c_readonly", c_writeable)
SECTIONS {
  INCLUDE text.ld
  INCLUDE rodata.ld
  INCLUDE data.ld
  INCLUDE zp.ld
  .bss (NOLOAD) : { INCLUDE bss-sections.ld } >console_ram
  INCLUDE bss-symbols.ld
  .noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >console_ram
  .console_ram (NOLOAD) : { *(.console_ram .console_ram.*) } >console_ram

  /* Used by zero-bss routines. */
  HIDDEN(__zero_bss_start = __bss_start + 1);
  HIDDEN(__zero_bss_size = __bss_size >= 2 ? __bss_size - 1 : 1);
  HIDDEN(__zero_zp_bss_start = __zp_bss_start + 1);
  HIDDEN(__zero_zp_bss_size = __zp_bss_size >= 2 ? __zp_bss_size - 1 : 1);
}
