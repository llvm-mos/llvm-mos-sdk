.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_joystick_scan(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-joystick_scan
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_joystick_scan
cx16_k_joystick_scan:
	jmp	__JOYSTICK_SCAN
