.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_fill_pixels(unsigned int count, unsigned int step, unsigned char color);
; llvm-mos:                               A/X                rc2/3                rc4
; llvm-mos aliases:                       A/X                r0                   r1L
; X16 kernal:                             r0                 r1                   A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_fill_pixels
;
.global cx16_k_fb_fill_pixels
cx16_k_fb_fill_pixels:
	save_X16_scratch
	ldy	__rc2		; NOTE: copy args backwards due to overlap
	sty	__r1		; r1 = step
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; r0 = count
	stx	__r0+1
	lda	__rc4		; A = color
	jsr	__FB_FILL_PIXELS
	restore_X16_scratch
	rts
