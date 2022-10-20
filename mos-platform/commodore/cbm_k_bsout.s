.text

#include <cbm_kernal.inc>

;
; void cbm_k_bsout (unsigned char C);
;
.global cbm_k_bsout
cbm_k_bsout:
	jmp $FFD2