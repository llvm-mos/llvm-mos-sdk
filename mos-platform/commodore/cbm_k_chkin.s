.text

;
; unsigned char cbm_k_chkin (unsigned char FN);
;
.global cbm_k_chkin
cbm_k_chkin:
	tax
	jsr __CHKIN
	bcs some_error
	lda #0 ; open was successful if .C = clear
some_error:
	rts
