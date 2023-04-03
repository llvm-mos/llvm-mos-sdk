.include "imag.inc"
.text

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

;
; void fb_set_8_pixels(unsigned char pattern, unsigned char color);
;                                    a                      x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_set_8_pixels
;
.global cx16_k_fb_set_8_pixels
cx16_k_fb_set_8_pixels:
				; a = pattern (already set)
				; x = color (already set)
	jmp __FB_SET_8_PIXELS
