.text

#include <cbm_kernal.inc>

__rs1 = __rc2
__rs2 = __rc4 

;
; unsigned char cbm_k_save(unsigned int start, unsigned int end);
;
.global cbm_k_save
cbm_k_save:
	sta __rs2 
	stx __rs2 + 1
	ldx __rc2
	ldy __rc2 + 1
	lda #__rs2
	jmp SAVE
	
