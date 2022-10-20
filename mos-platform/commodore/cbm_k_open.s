.text

#include <cbm_kernal.inc>

;
; unsigned char cbm_k_open (void);
;
.global cbm_k_open
cbm_k_open:
	jmp $FFC0
