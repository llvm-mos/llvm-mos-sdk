.include "imag.inc"
.text

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

;
; void fb_set_8_pixels_opaque(unsigned char pattern, unsigned char mask, unsigned char color1, unsigned char color2);
;                                           a                      x                   rc2                   rc3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_8_pixels_opaque
;
.global cx16_k_fb_set_8_pixels_opaque
cx16_k_fb_set_8_pixels_opaque:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
				; a = pattern (already set)
	stx	r0		; r0L = mask
	ldx	__rc2		; x = color1
	ldy	__rc3		; y = color2
	jsr	__FB_SET_8_PIXELS_OPAQUE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
