.text

#include <cbm_kernal.inc>

;
; unsigned char cbm_k_readst (void);
;
.global cbm_k_readst
cbm_k_readst:
	jmp READST