.section .comhdr, "aw", @progbits
_comhdr:
	.short _pblock /* address of pblock / relocation data */

