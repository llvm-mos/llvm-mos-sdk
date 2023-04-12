.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_put_char(unsigned char c, unsigned char wrapwordflag);
;                                            a                x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_put_char
;
.global cx16_k_console_put_char
cx16_k_console_put_char:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
				; a = c
	cpx	#1		; c = set if wrapwordflag >= 1
	jsr	__CONSOLE_PUT_CHAR
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
