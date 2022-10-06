MEMORY {
    zp : ORIGIN = 0, LENGTH = 64
    ram (rw) : ORIGIN = 0x200, LENGTH = 0xfe00
}

PHDRS {
	zp PT_NULL AT(0x0);
	load PT_LOAD AT(0x200);
	relo PT_NULL;
	symtab PT_NULL;
}

SECTIONS {
	.zp (NOLOAD) : {
		__zp_start = .;
		__zp_data_load_start = LOADADDR(.zp.data);
		__zp_data_size = SIZEOF(.zp.data);
	} >zp :zp

    INCLUDE zp-bss.ld
    INCLUDE zp-noinit.ld
	.zp : { __zp_end = .; } >zp

	.text : {
		BYTE (__zp_end - __zp_start) /* ZP size */
		BYTE ((__heap_start + 255) / 256) /* total memory size (pages) */
		SHORT (_pblock) /* address of pblock / relocation data */
		KEEP _pblock;
	} >ram :load

	.text : {
		BDOS = .;
		BYTE (0x4c) /* jump instruction for BDOS calls */
		SHORT (0) /* patched by loader */
		INCLUDE text-sections.ld
	} >ram :load

    .rodata : { INCLUDE rodata-sections.ld } >ram :load
    .data : {
		INCLUDE data-sections.ld
	} >ram :load

    .zp.data : {
		__zp_data_load_start = .;
		INCLUDE zp-data-sections.ld
		__zp_data_size = SIZEOF(.zp.data);
	} >zp AT>ram :NONE

	.pblock (NOLOAD) : {
		_pblock = .;
		*(.pblock)
	} >ram :NONE

	.bss (NOLOAD) : {
		__bss_start = .;
		*(.bss .bss.* COMMON)
		__bss_end = .;
		__bss_size = SIZEOF(.bss);
	} >ram

	.noinit (NOLOAD) : {
		*(.noinit .noinit.*)
		__heap_start = .;
		cpm_ram = .;
	} >ram

	.rela.text : {
	} :relo

	.rela.rodata : {
	} :relo

	.symtab : {
	} :symtab
}

