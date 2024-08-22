.text

;
; unsigned long cx16_k_rdtim (void);
;
.global cx16_k_rdtim
.section .text.cx16_k_rdtim,"axR",@progbits
cx16_k_rdtim:
	jsr __RDTIM	; kernal returns A/X/Y, llvm wants A/X/__rc2/0
	stz __rc2+1	; zero high byte
	sty __rc2	; A = H
			; X = M
			; A = L
	rts
