.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_joystick_get(unsigned char sticknum); // returns $YYYYXXAA (see docs, result negative if joystick not present)
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-joystick_get
;
.global cx16_k_joystick_get
cx16_k_joystick_get:
	jsr	__JOYSTICK_GET
	sty	__rc2
	sty	__rc3
	rts
