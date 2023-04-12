.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_init(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
;                                     a/x           rc2/3               rc4/5               rc6/7
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_init
;
.global cx16_k_console_init
cx16_k_console_init:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = x
	stx	__r0+1
				; __r1 = y (already set)
				; __r2 = width (already set)
				; __r3 = height (already set)
	jsr	__CONSOLE_INIT
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
