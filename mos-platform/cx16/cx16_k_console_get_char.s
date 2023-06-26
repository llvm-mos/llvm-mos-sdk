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
	save_X16_scratch
	jsr	__CONSOLE_GET_CHAR
	restore_X16_scratch
	rts
