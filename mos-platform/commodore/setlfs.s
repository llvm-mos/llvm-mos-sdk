.text

#include <cbm_kernal.inc>

;
; void cbm_k_setlfs (unsigned char LFN, unsigned char DEV, unsigned char SA);
;
.global cbm_k_setlfs
cbm_k_setlfs:
	ldy __rc2
	jmp SETLFS