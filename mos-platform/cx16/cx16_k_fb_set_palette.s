.include "imag.inc"
.include "cx16.inc"
.text

;
; void fb_set_palette(void *paladdr, unsigned char index, unsigned char count);
;                           rc2/3                  a                    x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_palette
;
.global cx16_k_fb_set_palette
cx16_k_fb_set_palette:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; __r0 = paladdr
	sty	__r0
	ldy	__rc2+1
	sty	__r0+1
				; a = index (already set)
				; x = count (already set)
	jsr	__FB_SET_PALETTE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
