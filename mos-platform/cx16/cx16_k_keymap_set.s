.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_keymap_set(const char* identifier);	// returns 0 on success
; llvm-mos:                                   rc2/3
; X16 kernal:                                 X/Y    C=0
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-keymap
;
.global cx16_k_keymap_set
.section .text.cx16_k_keymap_set,"axR",@progbits
cx16_k_keymap_set:
	ldx	__rc2			; X/Y = identifier
	ldy	__rc3
	clc				; C = clear for set keymap
	jsr	__KEYMAP
	lda	#0			; return 0 on success
	adc	#0			; return 1 on error (carry set)
	rts
