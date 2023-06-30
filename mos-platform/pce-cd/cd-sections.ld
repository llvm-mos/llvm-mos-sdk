SECTIONS {
	.text : { INCLUDE text-sections.ld } >c_ram
	.rodata : { INCLUDE rodata-sections.ld } >c_ram
	.data : { INCLUDE data-sections.ld } >c_ram
	.zp.data : { INCLUDE zp-data-sections.ld } >zp AT>c_ram
	__zp_data_load_start = LOADADDR(.zp.data);
	__zp_data_size = SIZEOF(.zp.data);
	.zp.bss (NOLOAD) : { INCLUDE zp-bss-sections.ld } >zp
	INCLUDE zp-bss-symbols.ld
	INCLUDE zp-noinit.ld
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
