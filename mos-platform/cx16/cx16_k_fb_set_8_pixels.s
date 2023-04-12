.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_set_8_pixels(unsigned char pattern, unsigned char color);
;                                    a                      x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_8_pixels
;
.global cx16_k_fb_set_8_pixels
cx16_k_fb_set_8_pixels:
				; a = pattern (already set)
				; x = color (already set)
	jmp __FB_SET_8_PIXELS
