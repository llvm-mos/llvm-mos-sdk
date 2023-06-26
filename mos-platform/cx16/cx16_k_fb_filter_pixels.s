.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_filter_pixels(void *filterfunc, unsigned int count);
; llvm-mos:                            rc2/3                    A/X
; llvm-mos aliases:                    r0                       A/X
; X16 kernal:                          r0                       r1
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_filter_pixels
;
.global cx16_k_fb_filter_pixels
cx16_k_fb_filter_pixels:
	save_X16_scratch
				; r0 = filterfunc (already set)
	sta	__r1		; r1 = count
	stx	__r1+1
	jsr	__FB_FILTER_PIXELS
	restore_X16_scratch
	rts
