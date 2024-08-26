.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_screen_set_charset(unsigned char charset_type, void *charsetaddr);
; llvm-mos:                                    A                   rc2/rc3
; X16-kernal:                                  A                   X/Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-screen_set_charset
;
.global cx16_k_screen_set_charset
.section .text.cx16_k_screen_set_charset,"axR",@progbits
cx16_k_screen_set_charset:
				; A = charset_type (already set)
	ldx	__rc2		; X/Y = charset_addr
	ldy	__rc2+1
	jmp	__SCREEN_SET_CHARSET
