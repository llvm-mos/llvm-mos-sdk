.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_screen_mode_set(unsigned char mode); // returns 0 on success
;                                                    a
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-screen_mode
;
.global cx16_k_screen_mode_set
cx16_k_screen_mode_set:
					; a = mode
	clc				; clear C for set screen mode
	jsr	__SCREEN_MODE
	lda	#0			; return 0 on success
	adc	#0			; return 1 on error (carry set)
	rts
