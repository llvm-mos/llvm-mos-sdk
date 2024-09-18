.include "imag.inc"
.include "cx16.inc"
.text

;
; void fb_set_palette(void *paladdr, unsigned char index, unsigned char count);
; llvm-mos:                 rc2/3                  A                    X
; llvm-mos aliases:         r0                     A                    X
; X16 kernal:               r0                     A                    X
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_palette
;
.global cx16_k_fb_set_palette
.section .text.cx16_k_fb_set_palette,"ax",@progbits
cx16_k_fb_set_palette:
				; r0 = paladdr (already set)
				; A = index (already set)
				; X = count (already set)
	jmp	__FB_SET_PALETTE
