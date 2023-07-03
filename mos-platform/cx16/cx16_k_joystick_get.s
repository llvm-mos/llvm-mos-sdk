.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_joystick_get(unsigned char sticknum); // returns $YYYYXXAA (see docs, result negative if joystick not present)
; llvm-mos:                              A
; X16 kernal:                            A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-joystick_get
;
.global cx16_k_joystick_get
cx16_k_joystick_get:
				; A = sticknum (already set)
	jsr	__JOYSTICK_GET
	sty	__rc2
	sty	__rc3
	rts
