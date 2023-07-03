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
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	jsr	__CONSOLE_GET_CHAR
	X16_kernal_pop_r6_r10
	rts
