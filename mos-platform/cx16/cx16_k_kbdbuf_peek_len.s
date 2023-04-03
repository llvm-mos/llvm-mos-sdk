.include "imag.inc"
.text

;
; unsigned char cx16_k_kbdbuf_peek_len(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_peek
;
.global cx16_k_kbdbuf_peek_len
cx16_k_kbdbuf_peek_len:
	jsr	__KBDBUF_PEEK
	txa
	rts
