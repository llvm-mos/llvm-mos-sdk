.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_put_char(unsigned char c, unsigned char wrapwordflag);
; llvm-mos:                                  A                X
; X16 kernal:                                A                C
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_put_char
;
.global cx16_k_console_put_char
.section .text.cx16_k_console_put_char,"axR",@progbits
cx16_k_console_put_char:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
				; A = c
	cpx	#1		; C = set if wrapwordflag >= 1
	jsr	__CONSOLE_PUT_CHAR
	X16_kernal_pop_r6_r10
	rts
