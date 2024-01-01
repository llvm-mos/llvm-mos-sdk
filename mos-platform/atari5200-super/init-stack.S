.include "imag.inc"

.global __do_init_stack

; Initialize soft stack pointer to $3c00, leaving 1KiB above for a
; limited text-mode
.section .init.100,"axR",@progbits
__do_init_stack:
	clc
	lda	#$00
	sta	__rc0
	lda	#$3c
	sta	__rc1
