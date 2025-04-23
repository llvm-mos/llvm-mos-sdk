.include "imag.inc"
.include "cx16.inc"
.text

; unsigned char cx16_k_sprite_set_image(unsigned char num, unsigned char w, unsigned char h, unsigned char maskflag, void *imageaddr, void *maskaddr, unsigned char bpp); // returns 0 on success
; llvm-mos:                                           A                  X              rc2                rc3             rc4/5            rc6/7                   rc8
; llvm-mos aliases:                                   A                  X              r0L                r0H             r1               r2                      r3L
; X16 kernal:                                         A                  X              Y                  C               r0               r1                      r2L
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-sprite_set_image
;
.global cx16_k_sprite_set_image
.section .text.cx16_k_sprite_set_image,"ax",@progbits
cx16_k_sprite_set_image:
	ldy	__rc2		; save h in r4 temp
	sty	__r4
	ldy	__rc3		; load maskflag
	cpy	#1		; C = set if maskflag >= 1
	ldy	__rc4
	sty	__r0		; r0 = imageaddr
	ldy	__rc4+1
	sty	__r0+1
	ldy	__rc6
	sty	__r1		; r1 = maskaddr
	ldy	__rc6+1
	sty	__r1+1
	ldy	__rc8
	sty	__r2		; r2 = bpp
				; A = num (already set)
				; X = w (already set)
	ldy	__r4		; Y = h
	jsr	__SPRITE_SET_IMAGE
	lda	#0		; return 0 on success
	adc	#0		; return 1 on error (carry set)
	rts
