.include "imag.inc"

.section .init.400,"ax",@progbits
	; make sure flags are in a sane state
	cld
	cli
	; tell dodo where the software stack pointer is
	lda #__rc0
	sta $00
	; Init hardware stack pointer
	ldx #$FF
	txs
