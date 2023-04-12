.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_console_get_char(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_get_char
;
.global cx16_k_console_get_char
cx16_k_console_get_char:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	jsr	__CONSOLE_GET_CHAR
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
