.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned long cx16_k_entropy_get(void); // returns 24-bit value
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-entropy_get
;
.global cx16_k_entropy_get
cx16_k_entropy_get:
	jsr	__ENTROPY_GET
	stz	__rc3
	sty	__rc2
	rts
