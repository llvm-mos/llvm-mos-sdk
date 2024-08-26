.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_kbdbuf_put(unsigned char c);
; llvm-mos:                            A
; X16 kernal:                          A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_put
;
.global cx16_k_kbdbuf_put
.section .text.cx16_k_kbdbuf_put,"axR",@progbits
cx16_k_kbdbuf_put:
				; A = c (already set)
	jmp	__KBDBUF_PUT
