.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_get_pixels(void *pixeladdr, unsigned int count);
;                          rc2/3                   a/x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_get_pixels
;
.global cx16_k_fb_get_pixels
cx16_k_fb_get_pixels:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; __r0 = pixeladdr
	sty	__r0
	ldy	__rc2+1
	sty	__r0+1
	sta	__r1		; __r1 = count
	stx	__r1+1
	jsr	__FB_GET_PIXELS
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
