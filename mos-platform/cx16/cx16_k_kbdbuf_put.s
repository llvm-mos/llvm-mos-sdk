.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_kbdbuf_put(unsigned char c);
;                                      a
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_put
;
.global cx16_k_kbdbuf_put
cx16_k_kbdbuf_put:
	jmp	__KBDBUF_PUT
