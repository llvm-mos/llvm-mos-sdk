.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_cursor_next_line(unsigned int x);
; llvm-mos:                                  A/X
; llvm-mos alias:                            A/X
; X16 kernal:                                r0

;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_cursor_next_line
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_fb_cursor_next_line
cx16_k_fb_cursor_next_line:
	sta	__r0		; __r0 = x
	stx	__r0+1
	jmp	__FB_CURSOR_NEXT_LINE
