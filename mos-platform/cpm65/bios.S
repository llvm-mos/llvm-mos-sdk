.section .init.20, "Rax", @progbits
__do_setup_bios:
	ldy #38
	jsr BDOS
	sta BIOS+1
	stx BIOS+2

.text

.global BIOS
BIOS:
	jmp 0 ; patched by startup code

