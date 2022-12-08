.include "imag.inc"
.text

;
; unsigned char cbm_k_save(unsigned int start, unsigned int end);
;
.global cbm_k_save
cbm_k_save:
	sta __rc4
	stx __rc5
	ldx __rc2
	ldy __rc3
	lda #__rc4
	jmp __SAVE
