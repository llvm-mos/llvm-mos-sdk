.text

#include <cbm_kernal.inc>

;
; unsigned char cbm_k_getin (void);
;
.global cbm_k_getin
cbm_k_getin:
	jmp GETIN