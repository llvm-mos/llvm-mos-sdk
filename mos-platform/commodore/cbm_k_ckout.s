.include "imag.inc"
.text

;
; unsigned char cbm_k_ckout(unsigned char FN);
;
.global cbm_k_ckout
cbm_k_ckout:
	tax
	jsr __CKOUT
	ldx #0
	bcs someerror
	lda #0
someerror:
	rts
