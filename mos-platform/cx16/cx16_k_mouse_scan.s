.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_mouse_scan(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-mouse_scan
;
.global cx16_k_mouse_scan
cx16_k_mouse_scan:
	jmp	__MOUSE_SCAN
