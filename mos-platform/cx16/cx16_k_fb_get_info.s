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
; typedef struct { unsigned int width, height; unsigned char depth; } cx16_fb_info_t;
; void cx16_k_fb_get_info(cx16_fb_info_t *info_ptr);
;                                         rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_get_info
;
.global cx16_k_fb_get_info
cx16_k_fb_get_info:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; save rc2/3
	phy
	ldy	__rc2+1
	phy
	jsr	__FB_GET_INFO
	ply			; restore rc2/3
	sty	__rc2+1
	ply
	sty	__rc2
	ldy	#5-1		; offset to depth
	sta	(__rc2),y	; store depth to info_ptr
	dey			; copy remaining 4 bytes
copywh:
	lda	r0,y		; from r0 & r1
	sta	(__rc2),y	; to info_ptr
	dey
	bpl	copywh
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
