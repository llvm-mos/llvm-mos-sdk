.text

#include <cbm_kernal.inc>

;
; unsigned cbm_k_iobase (void);
;
.global cbm_k_iobase
	jsr IOBASE
	txa
	sty __rc2
	ldx __rc2
	rts
	