.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_set_8_pixels_opaque(unsigned char pattern, unsigned char mask, unsigned char color1, unsigned char color2);
;                                           a                      x                   rc2                   rc3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_8_pixels_opaque
;
.global cx16_k_fb_set_8_pixels_opaque
cx16_k_fb_set_8_pixels_opaque:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
				; a = pattern (already set)
	stx	__r0		; __r0L = mask
	ldx	__rc2		; x = color1
	ldy	__rc3		; y = color2
	jsr	__FB_SET_8_PIXELS_OPAQUE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
