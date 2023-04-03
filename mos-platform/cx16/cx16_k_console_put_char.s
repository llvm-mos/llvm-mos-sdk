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
; void cx16_k_console_put_char(unsigned char c, unsigned char wrapwordflag);
;                                            a                x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_put_char
;
.global cx16_k_console_put_char
cx16_k_console_put_char:
				; a = c
	cpx	#1		; c = set if wrapwordflag >= 1
	jmp	__CONSOLE_PUT_CHAR
