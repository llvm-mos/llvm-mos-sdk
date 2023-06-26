.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_savehl(void *startaddr, void *endaddr_plusone); // returns 0 on success
;                                   rc2/3            rc4/5
; Not documented on https://github.com/X16Community/x16-docs
; similar to cbm_k_save, but no two byte header written
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_savehl
cbm_k_savehl:
	ldx	__rc4		; X/Y = end
	ldy	__rc4+1
	lda	#__rc2		; A = &startaddr
	jsr	__SAVEHL
	bcs	1f		; branch on error
	lda	#0
1:	rts
