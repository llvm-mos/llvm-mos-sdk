.include "imag.inc"

.text

;
; void *cbm_k_load(unsigned char flag, void *startaddr);
;                                a           rc2/3
;
.global cbm_k_load
cbm_k_load:
	ldx __rc2
	ldy __rc2+1
	jsr __LOAD
	bcc noerror
	; error code in a ;
	ldx #0
	rts
noerror:
	txa
	sty __rc2
	ldx __rc2
	rts
