.include "imag.inc"

.text

;
; unsigned int cbm_k_load(unsigned char flag, unsigned addr);
;
.global cbm_k_load
cbm_k_load:
	ldy __rc2
	jsr __LOAD
	bcs someerror
	lda #0
	tax
someerror:
	rts
