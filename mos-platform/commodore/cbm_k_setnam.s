.include "imag.inc"

.text

;
; void cbm_k_setnam (const char* Name);
;
.global cbm_k_setnam
cbm_k_setnam:
	lda __rc2
	pha
	lda __rc3
	pha
	jsr strlen
	sta __rc2
	pla
	tay
	pla
	tax
	lda __rc2
	jmp __SETNAM
