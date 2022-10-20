.text

#include <cbm_kernal.inc>

;
; void cbm_k_talk (unsigned char dev);
;
.global cbm_k_talk
cbm_k_talk:
	jmp $FFB4