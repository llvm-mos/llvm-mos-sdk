.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_macptr(unsigned char count, unsigned char noadvance, void *destaddr); // return negative if not supported
; llvm-mos:                        A                    X                rc2/3
; X16 kernal:                      A                    C                X/Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-macptr
;
.global cx16_k_macptr
.section .text.cx16_k_macptr,"ax",@progbits
cx16_k_macptr:
				; A = count
	cpx	#1		; C = set if noadvance >= 1
	ldx	__rc2		; X/Y = destaddr
	ldy	__rc2+1
	jsr	__MACPTR
	bcc	noerror
	lda	#$FF		; -1 on error
	tax
	sta	__rc2
	sta	__rc3
	rts
noerror:
	txa
	sty	__rc2
	ldx	__rc2
	stz	__rc2		; zero extend return
	stz	__rc3
	rts
