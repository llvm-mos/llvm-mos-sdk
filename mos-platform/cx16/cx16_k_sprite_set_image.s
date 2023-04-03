.include "imag.inc"

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

.text

; unsigned char cx16_k_sprite_set_image(unsigned char num, unsigned char w, unsigned char h, unsigned char maskflag, void *imageaddr, void *maskaddr, unsigned char bpp); // returns 0 on success
;                                                     a                  x              rc2                rc3             rc4/5            rc6/7                   rc8
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-sprite_set_image
;
.global cx16_k_sprite_set_image
cx16_k_sprite_set_image:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc4		; r0 = imageaddr
	sty	r0
	ldy	__rc4+1
	sty	r0+1
	ldy	__rc6		; r1 = maskaddr
	sty	r1
	ldy	__rc6+1
	sty	r1+1
	ldy	__rc8		; r2 = bpp
	sty	r2
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
