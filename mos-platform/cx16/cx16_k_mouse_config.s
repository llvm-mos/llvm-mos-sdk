.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_mouse_config(unsigned char showmouse, unsigned char xsize8, unsigned char ysize8);
; llvm-mos:                              A                        X                     rc2
; llvm-mos aliases:                      A                        X                     r0L
; X16 kernal:                            A                        X                     Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-mouse_config
;
.global cx16_k_mouse_config
cx16_k_mouse_config:
				; A = showmouse (already set)
				; X = xsize8 (already set)
	ldy	__rc2		; Y = ysize8
	jmp	__MOUSE_CONFIG
