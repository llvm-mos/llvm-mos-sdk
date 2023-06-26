.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_cursor_position(unsigned int x, unsigned int y);
; llvm-mos:                                 A/X           rc2/3
; llvm-mos aliases:                         A/X           r0
; X16 kernal:                               r0            r1
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_cursor_position
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_fb_cursor_position
cx16_k_fb_cursor_position:
	ldy	__rc2		; NOTE: copy args backwards due to overlap
	sty	__r1		; r1 = y
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; r0 = x
	stx	__r0+1
	jmp	__FB_CURSOR_POSITION
