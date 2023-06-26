.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_screen_set_charset(unsigned char charset_type, void *charsetaddr);
;                                              a                   rc2/rc3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-screen_set_charset
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_screen_set_charset
cx16_k_screen_set_charset:
				; A = charset_type (already set)
	ldx	__rc2		; X/Y = charset_addr
	ldy	__rc2+1
	jmp	__SCREEN_SET_CHARSET
