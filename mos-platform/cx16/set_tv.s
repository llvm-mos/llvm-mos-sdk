.include "imag.inc"
.include "cx16.inc"
.text

;
; void set_tv(unsigned char type);    // set video signal type using TV_* enum constant
; llvm-mos:                 A
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/set_tv.s
;
.global set_tv
.section .text.set_tv,"ax",@progbits
set_tv:
	stz	VERA_CTRL	; set DCSEL=0 to access DC_VIDEO
	eor	VERA_DC_VIDEO	; eor in current register bits
	and	#$0F		; don't alter layer or sprite bits
	eor	VERA_DC_VIDEO	; eor in video mode bits again
	sta	VERA_DC_VIDEO	; store result with low 4 bits altered
	rts
