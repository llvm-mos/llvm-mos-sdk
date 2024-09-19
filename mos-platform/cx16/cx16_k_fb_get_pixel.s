.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char cx16_k_fb_get_pixel(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_get_pixel
;
.global cx16_k_fb_get_pixel
.section .text.cx16_k_fb_get_pixel,"ax",@progbits
cx16_k_fb_get_pixel:
	jsr	__FB_GET_PIXEL
	ldx	#0
	rts
