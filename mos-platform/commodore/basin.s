.text

#include <cbm_kernal.inc>
;
; unsigned char cbm_k_basin (void);
;
.global cbm_k_basin
cbm_k_basin:
	jmp BASIN
	