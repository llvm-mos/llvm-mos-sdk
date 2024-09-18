.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_set_8_pixels_opaque(unsigned char pattern, unsigned char mask, unsigned char color1, unsigned char color2);
; llvm-mos:                                        A                      X                   rc2                   rc3
; llvm-mos aliases:                                A                      X                   r0L                   r0H
; X16 kernal:                                      A                      r0L                 X                     Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_8_pixels_opaque
;
.global cx16_k_fb_set_8_pixels_opaque
.section .text.cx16_k_fb_set_8_pixels_opaque,"ax",@progbits
cx16_k_fb_set_8_pixels_opaque:
	stx	__r0		; r0L = mask
	ldx	__rc2		; X = color1
	ldy	__rc3		; Y = color2
				; A = pattern (already set)
	jmp	__FB_SET_8_PIXELS_OPAQUE
