.include "imag.inc"

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

.text

;
; void cx16_k_console_init(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
;                                     a/x           rc2/3               rc4/5               rc6/7
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_init
;
.global cx16_k_console_init
cx16_k_console_init:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	sta	r0		; r0 = x
	stx	r0+1
				; r1 = y (already set)
				; r2 = width (already set)
				; r3 = height (already set)
	jsr	__CONSOLE_INIT
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
