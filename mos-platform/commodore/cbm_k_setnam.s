.text

#include <cbm_kernal.inc>
__rs1 = __rc2

;
; void cbm_k_setnam (const char* Name);
;	
.global cbm_k_setnam
cbm_k_setnam:
	lda __rs1 
	pha
	lda __rs1 + 1
	pha
	jsr strlen
	sta __rc2
	pla 
	tay
	pla 
	tax
	lda __rc2
	jmp SETNAM