.include "imag.inc"
.include "cx16.inc"
.text

;
; const char* cx16_k_keymap_get_id(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-keymap
;
.global cx16_k_keymap_get_id
.section .text.cx16_k_keymap_get_id,"axR",@progbits
cx16_k_keymap_get_id:
	sec				; set C for get keymap identifier
	jsr	__KEYMAP
	txa
	sty	__rc2
	ldx	__rc2
	rts
