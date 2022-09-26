.section .init.20, "axR", @progbits
__do_setup_bios:
	ldy #38
	jsr BDOS
	sta bios+1
	stx bios+2

.text

.global bios
bios:
	jmp 0 ; patched by startup code

