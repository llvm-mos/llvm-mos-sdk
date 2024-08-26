.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_fill_pixels(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int count);
; llvm-mos:                              A/X            rc2/3            rc4/5            rc6/7               rc8/9
; llvm-mos aliases:                      A/X            r0               r1               r2                  r3
; X16 kernal:                            r0             r1               r2               r3                  r4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_move_pixels
;
.global cx16_k_fb_fill_pixels
.section .text.cx16_k_fb_fill_pixels,"axR",@progbits
cx16_k_fb_fill_pixels:
	ldy	__rc8		; NOTE: copy args backwards due to overlap
	sty	__r4		; r4 = count
	ldy	__rc8+1
	sty	__r4+1
	ldy	__rc6
	sty	__r3		; r3 = height
	ldy	__rc6+1
	sty	__r3+1
	ldy	__rc4
	sty	__r2		; r2 = width
	ldy	__rc4+1
	sty	__r2+1
	ldy	__rc2
	sty	__r1		; r1 = y
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; r0 = x
	stx	__r0+1
	jmp	__FB_MOVE_PIXELS
