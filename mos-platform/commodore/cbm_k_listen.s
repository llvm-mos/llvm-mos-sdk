.text

#include <cbm_kernal.inc>

;
; void cbm_k_listen (unsigned char dev);
;
.global cbm_k_listen
cbm_k_listen:
	jmp LISTEN