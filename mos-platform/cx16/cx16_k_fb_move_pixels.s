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
; void fb_move_pixels(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int count);
;                                 a/x            rc2/3            rc4/5            rc6/7               rc8/9
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_move_pixels
;
.global cx16_k_fb_fill_pixels
cx16_k_fb_fill_pixels:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	sta	r0		; r0 = sx
	stx	r0+1
				; r1 = sy (already set)
				; r2 = tx (already set)
				; r3 = ty (already set)
				; r4 = count (already set)
	jsr	__FB_MOVE_PIXELS
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
