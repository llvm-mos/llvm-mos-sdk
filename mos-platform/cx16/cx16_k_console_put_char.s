.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_put_char(unsigned char c, unsigned char wrapwordflag);
;                                            A                X
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_put_char
;
.global cx16_k_console_put_char
cx16_k_console_put_char:
	save_X16_scratch
				; A = c
	cpx	#1		; C = set if wrapwordflag >= 1
	jsr	__CONSOLE_PUT_CHAR
	restore_X16_scratch
	rts
