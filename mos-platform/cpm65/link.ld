MEMORY {
    zp : ORIGIN = 0, LENGTH = 0x70
    ram (rw) : ORIGIN = 0x200, LENGTH = 0xfe00
}

PHDRS {
	load PT_LOAD;
	init PT_LOAD;
	relo PT_NULL;
	symtab PT_NULL;
}

SECTIONS {
	.zp.bss (NOLOAD) : { INCLUDE zp-bss-sections.ld } >zp :NONE
	INCLUDE zp-bss-symbols.ld

	.text : {
		cpm_header = .;
		BYTE (SIZEOF(.zp)) /* ZP size */
		BYTE ((__heap_start + 255) / 256) /* total memory size (pages) */
		SHORT (_pblock) /* address of pblock / relocation data */

		KEEP _pblock;

		BDOS = .;
		BYTE (0x4c) /* jump instruction for BDOS calls */
		SHORT (0) /* patched by loader */
	} >ram :load

	INCLUDE text.ld
	INCLUDE rodata.ld
	INCLUDE data.ld

	.zp.data : {
		__zp_data_start = .;
		*(.zp.data .zp.data.*)
		*(.zp.rodata .zp.rodata.*)
	} >zp AT>ram :init
	INCLUDE zp-data-symbols.ld

	.pblock (NOLOAD) : {
		_pblock = .;
		*(.pblock)
	} >ram :NONE

	INCLUDE bss.ld
	INCLUDE noinit.ld

	INCLUDE zp-noinit.ld

	.rela.text : {
	} :relo

	.rela.rodata : {
	} :relo

	.symtab : {
	} :symtab

	PROVIDE (cpm_ram = __heap_start);

}

/* The result of this is actually irrelevant --- the elftocpm65 tool will
 * rewrite the output file and add relocation information. The only reason this
 * is here is to trick the linker into emitting the $FILENAME.elf file which
 * elftocpm65 reads. */

OUTPUT_FORMAT {
    TRIM(ram)
}

