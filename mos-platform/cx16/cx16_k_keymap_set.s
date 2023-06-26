.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_keymap_set(const char* identifier);	// returns 0 on success
;                                             rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-keymap
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_keymap_set
cx16_k_keymap_set:
	ldx	__rc2			; X/Y = identifier
	ldy	__rc3
	clc				; C = clear for set keymap
	jsr	__KEYMAP
	lda	#0			; return 0 on success
	adc	#0			; return 1 on error (carry set)
	rts
