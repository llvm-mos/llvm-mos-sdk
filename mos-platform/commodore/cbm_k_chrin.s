.text

#include <cbm_kernal.inc>

;
; unsigned char cbm_k_chrin (void);
;
.global cbm_k_chrin
cbm_k_chrin:
	jmp CHRIN
