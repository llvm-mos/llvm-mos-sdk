.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_joystick_get(unsigned char sticknum); // returns $YYYYXXAA (see docs, result negative if joystick not present)
;                                        a
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-joystick_get
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_joystick_get
cx16_k_joystick_get:
				; A = sticknum (already set)
	jsr	__JOYSTICK_GET
	sty	__rc2
	sty	__rc3
	rts
