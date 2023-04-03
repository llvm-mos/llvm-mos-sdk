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
; void fb_set_palette(void *paladdr, unsigned char index, unsigned char count);
;                           rc2/3                  a                    x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_palette
;
.global cx16_k_fb_set_palette
cx16_k_fb_set_palette:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; r0 = paladdr
	sty	r0
	ldy	__rc2+1
	sty	r0+1
				; a = index (already set)
				; x = count (already set)
	jsr	__FB_SET_PALETTE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
