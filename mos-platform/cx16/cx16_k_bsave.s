.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_bsave(void *startaddr, void *endaddr_plusone); // returns 0 on success
; llvm-mos:                         rc2/3            rc4/5
; X16-kernel:                       A                X/Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-bsave
; similar to cbm_k_save, but no two byte header written (aka savehl in X16 kernel source)
;
.global cx16_k_bsave
.section .text.cx16_k_bsave,"axR",@progbits
cx16_k_bsave:
	ldx	__rc4		; X/Y = end
	ldy	__rc4+1
	lda	#__rc2		; A = &startaddr
	jsr	__BSAVE
	bcs	1f		; branch on error
	lda	#0
1:	rts
