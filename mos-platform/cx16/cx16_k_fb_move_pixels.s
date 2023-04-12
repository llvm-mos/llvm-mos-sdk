.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_fill_pixels(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int count);
;                                 a/x            rc2/3            rc4/5            rc6/7               rc8/9
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_move_pixels
;
.global cx16_k_fb_fill_pixels
cx16_k_fb_fill_pixels:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = sx
	stx	__r0+1
				; __r1 = sy (already set)
				; __r2 = tx (already set)
				; __r3 = ty (already set)
				; __r4 = count (already set)
	jsr	__FB_MOVE_PIXELS
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
