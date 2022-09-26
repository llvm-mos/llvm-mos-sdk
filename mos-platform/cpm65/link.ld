__rc0 = 0;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 31, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 32
    ram  (rw) : ORIGIN = 0x000, LENGTH = 0x10000
}

SECTIONS {
	.text : {
		BYTE (__zp_end) /* ZP size */
		BYTE ((__heap_start + 255) / 256) /* total memory size (pages) */
		SHORT (_pblock) /* address of pblock / relocation data */
		KEEP _pblock;
	} >ram

	.text : {
		BDOS = .;
		BYTE (0x4c) /* jump instruction for BDOS calls */
		SHORT (0) /* patched by loader */
		INCLUDE text-sections.ld
	} >ram

    .rodata : { INCLUDE rodata-sections.ld } >ram
    .data : { INCLUDE data-sections.ld } >ram

    .zp.data : { INCLUDE zp-data-sections.ld } >zp AT>ram
    INCLUDE zp-data-symbols.ld
    INCLUDE zp-bss.ld
    INCLUDE zp-noinit.ld
	.zp : { __zp_end = .; } >zp

	.pblock (NOLOAD) : {
		_pblock = .;
		*(.pblock)
	} >ram

    INCLUDE bss.ld
    INCLUDE noinit.ld
}

