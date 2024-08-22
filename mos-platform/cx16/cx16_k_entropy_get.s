.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned long cx16_k_entropy_get(void); // returns 24-bit value
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-entropy_get
;
.global cx16_k_entropy_get
.section .text.cx16_k_entropy_get,"axR",@progbits
cx16_k_entropy_get:
	jsr	__ENTROPY_GET
	stz	__rc2+1		; zero [31:24]
	sty	__rc2		; set  [23:16]
				; A/X  [15:0]
	rts
