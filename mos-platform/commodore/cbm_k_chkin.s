.text

;
; unsigned char cbm_k_chkin (unsigned char FN);
;
.global cbm_k_chkin
cbm_k_chkin:
	tax
	jmp __CHKIN
	
