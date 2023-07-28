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
	; store error code in A
	sta __rc2
	ldx #0
	stx __rc2+1
	rts
noerror:
	stx __rc2	; store end+1 low
	sty __rc2+1	; store end+1 high
	rts
