.include "imag.inc"
.text

;
; unsigned char cbm_k_save(void *startaddr, void *endaddr_plusone);
;                                rc2/3            rc4/5
;
.global cbm_k_save
cbm_k_save:
	ldx __rc4
	ldy __rc5
	lda #__rc2
	jsr __SAVE
	bcs someerror
	lda #0
someerror:
	rts
