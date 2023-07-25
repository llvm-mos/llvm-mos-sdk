.text

;
; unsigned long cbm_k_rdtim (void);
;
.global cbm_k_rdtim
cbm_k_rdtim:
	jsr __RDTIM	; returns Y/X/A
	sta __rc2	; A = H
	lda #$00
	sta __rc2+1	; zero high byte
			; X = M
	tya		; Y = L
	rts
