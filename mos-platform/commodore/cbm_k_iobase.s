.include "imag.inc"

.text

;
; unsigned cbm_k_iobase (void);
;
.global cbm_k_iobase
	jsr __IOBASE
	txa
	sty __rc2
	ldx __rc2
	rts
	