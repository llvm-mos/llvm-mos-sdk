.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_cursor_next_line(unsigned int x);
;                                            a/x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_cursor_next_line
;
.global cx16_k_fb_cursor_next_line
cx16_k_fb_cursor_next_line:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = x
	stx	__r0+1
	jsr	__FB_CURSOR_NEXT_LINE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
