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
		__rc0 = .; BYTE (0);
		__rc1 = .; BYTE (0);
		__rc2 = .; BYTE (0);
		__rc3 = .; BYTE (0);
		__rc4 = .; BYTE (0);
		__rc5 = .; BYTE (0);
		__rc6 = .; BYTE (0);
		__rc7 = .; BYTE (0);
		__rc8 = .; BYTE (0);
		__rc9 = .; BYTE (0);
		__rc10 = .; BYTE (0);
		__rc11 = .; BYTE (0);
		__rc12 = .; BYTE (0);
		__rc13 = .; BYTE (0);
		__rc14 = .; BYTE (0);
		__rc15 = .; BYTE (0);
		__rc16 = .; BYTE (0);
		__rc17 = .; BYTE (0);
		__rc18 = .; BYTE (0);
		__rc19 = .; BYTE (0);
		__rc20 = .; BYTE (0);
		__rc21 = .; BYTE (0);
		__rc22 = .; BYTE (0);
		__rc23 = .; BYTE (0);
		__rc24 = .; BYTE (0);
		__rc25 = .; BYTE (0);
		__rc26 = .; BYTE (0);
		__rc27 = .; BYTE (0);
		__rc28 = .; BYTE (0);
		__rc29 = .; BYTE (0);
		__rc30 = .; BYTE (0);
		__rc31 = .; BYTE (0);

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

