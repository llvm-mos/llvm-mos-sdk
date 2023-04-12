.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_fill_pixels(unsigned int count, unsigned int step, unsigned char color);
;                                         a/x                rc2/3                rc4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_fill_pixels
;
.global cx16_k_fb_fill_pixels
cx16_k_fb_fill_pixels:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = count
	stx	__r0+1
				; __r1 = step (already set)
	lda	__rc4		; a = color
	jsr	__FB_FILL_PIXELS
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
