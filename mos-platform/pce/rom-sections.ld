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
	} >c_rom
	.rodata : { INCLUDE rodata-sections.ld } >c_rom
	.data : { INCLUDE data-sections.ld } >c_ram AT>c_rom
	__data_load_start = LOADADDR(.data);
	__data_size = SIZEOF(.data);
	.zp.data : { INCLUDE zp-data-sections.ld } >zp AT>c_rom
	__zp_data_load_start = LOADADDR(.zp.data);
	__zp_data_size = SIZEOF(.zp.data);
	.zp.bss (NOLOAD) : { INCLUDE zp-bss-sections.ld } >zp
	INCLUDE zp-bss-symbols.ld
	INCLUDE zp-noinit.ld
	.bss (NOLOAD) : { INCLUDE bss-sections.ld } >c_ram
	INCLUDE bss-symbols.ld
	.noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >c_ram

	/* Used by zero-bss routines. */
	HIDDEN(__zero_bss_start = __bss_start + 1);
	HIDDEN(__zero_bss_size = __bss_size >= 2 ? __bss_size - 1 : 1);
	HIDDEN(__zero_zp_bss_start = __zp_bss_start + 1);
	HIDDEN(__zero_zp_bss_size = __zp_bss_size >= 2 ? __zp_bss_size - 1 : 1);
}
