.include "imag.inc"

.text

;
; unsigned char cbm_k_open(void);
;
.global cbm_k_open
cbm_k_open:
	jsr __OPEN
	bcs some_error
	lda #0 ; open was successful if .C = clear
some_error:
	rts
