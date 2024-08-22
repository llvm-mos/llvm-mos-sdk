.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_kbdbuf_get_modifiers(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_get_modifiers
;
.global cx16_k_kbdbuf_get_modifiers
.section .text.cx16_k_kbdbuf_get_modifiers,"axR",@progbits
cx16_k_kbdbuf_get_modifiers:
	jsr	__KBDBUF_GET_MODIFIERS
	rts
