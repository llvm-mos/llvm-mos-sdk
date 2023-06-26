.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_kbdbuf_put(unsigned char c);
;                                      a
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_put
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_kbdbuf_put
cx16_k_kbdbuf_put:
				; A = c (already set)
	jmp	__KBDBUF_PUT
