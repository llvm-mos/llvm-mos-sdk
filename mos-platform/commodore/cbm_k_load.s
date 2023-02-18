.include "imag.inc"

.text

;
; unsigned int cbm_k_load(unsigned char flag, unsigned addr);
;
.global cbm_k_load
cbm_k_load:
	ldy __rc2
	jsr __LOAD
	bcs noerror
	; error code in a ;
	ldx #0
	rts
noerror:
	txa
	sty __rc2
	ldx __rc2
	rts
