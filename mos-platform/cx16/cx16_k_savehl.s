.include "imag.inc"
.text

;
; unsigned char cx16_k_savehl(void *startaddr, void *endaddr_plusone); // returns 0 on success
;                                   rc2/3            rc4/5
;
; similar to cbm_k_save, but no two byte header written
.global cx16_k_savehl
cbm_k_savehl:
	ldx	__rc4		; x/y = end
	ldy	__rc4+1
	lda	#__rc2		; a = &startaddr
	jsr	__SAVEHL
	bcs	someerror
	lda	#0
someerror:
	rts
