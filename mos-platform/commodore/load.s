.text

#include <cbm_kernal.inc>

;
; unsigned int cbm_k_load(unsigned char flag, unsigned addr);
;
.global cbm_k_load
cbm_k_load:
	ldy __rc2
	jmp LOAD
