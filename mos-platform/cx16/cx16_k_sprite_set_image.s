.include "imag.inc"
.include "cx16.inc"
.text

; unsigned char cx16_k_sprite_set_image(unsigned char num, unsigned char w, unsigned char h, unsigned char maskflag, void *imageaddr, void *maskaddr, unsigned char bpp); // returns 0 on success
;                                                     a                  x              rc2                rc3             rc4/5            rc6/7                   rc8
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-sprite_set_image
;
.global cx16_k_sprite_set_image
cx16_k_sprite_set_image:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc4		; __r0 = imageaddr
	sty	__r0
	ldy	__rc4+1
	sty	__r0+1
	ldy	__rc6		; __r1 = maskaddr
	sty	__r1
	ldy	__rc6+1
	sty	__r1+1
	ldy	__rc8		; __r2 = bpp
	sty	__r2
	ldy	__rc3		; maskflag
	cpy	#1		; carry = maskflag >= 1
				; a = num
				; x = w
	ldy	__rc2		; y = h
	jsr	__SPRITE_SET_IMAGE
	lda	#0		; return 0 on success
	adc	#0		; return 1 on error (carry set)
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
