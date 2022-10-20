.text

#include <cbm_kernal.inc>

;
; void cbm_k_tksa (unsigned char addr);
;
.global cbm_k_tksa
cbm_k_tksa: 
	jmp $FF96