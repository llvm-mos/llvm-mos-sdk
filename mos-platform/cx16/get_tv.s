.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char get_tv(void);    // return TV_* enum constant for current video signal type
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/get_tv.s
;
.global get_tv
get_tv:
	stz	VERA_CTRL	; set DCSEL=0 to access DC_VIDEO
	lda	VERA_DC_VIDEO	; load DC_VIDEO
	and	#$0F		; mask out non-mode bits
	ldx	#0		; zero extend
1:	rts
