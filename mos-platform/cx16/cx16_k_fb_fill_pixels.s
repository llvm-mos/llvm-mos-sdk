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
; void cx16_k_fb_fill_pixels(unsigned int count, unsigned int step, unsigned char color);
;                                         a/x                rc2/3                rc4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_fill_pixels
;
.global cx16_k_fb_fill_pixels
cx16_k_fb_fill_pixels:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	sta	r0		; r0 = count
	stx	r0+1
				; r1 = step (already set)
	lda	__rc4		; a = color
	jsr	__FB_FILL_PIXELS
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
