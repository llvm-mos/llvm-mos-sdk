.include "imag.inc"
.include "cx16.inc"
.text

;
; int cx16_k_kbdbuf_peek(void); // returns negative if empty
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_peek
;
.global cx16_k_kbdbuf_peek
cx16_k_kbdbuf_peek:
	jsr	__KBDBUF_PEEK
	beq	empty
	ldx	#$00
	rts
empty:
	ldx	#$ff		; return -1 if empty
	txa
	rts
