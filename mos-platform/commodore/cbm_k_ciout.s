.text

#include <cbm_kernal.inc>

;
; void cbm_k_ciout (unsigned char C);
;
.global cbm_k_ciout
cbm_k_ciout:
	jmp $FFA8