.include "imag.inc"

.text

;
; void *cbm_k_load(unsigned char verifyflag, void *startaddr);	// if result address < 256, likely an error code
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
	stx __rc2	; store end+1 low
	sty __rc2+1	; store end+1 high
	rts
