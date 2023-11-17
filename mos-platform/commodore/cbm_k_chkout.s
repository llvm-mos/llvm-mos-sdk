.text

;
; unsigned char cbm_k_chkout (unsigned char FN);
;
.global cbm_k_chkout
cbm_k_chkout:
	tax
	jsr __CHKOUT
	bcs some_error
	lda #0 ; open was successful if .C = clear
some_error:
	rts
