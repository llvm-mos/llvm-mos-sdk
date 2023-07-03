.include "imag.inc"
.include "cx16.inc"
.text

;
; signed char get_ostype(void);  // return ROM build version (negative pre-release, -1=custom)
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/get_ostype.s
;
.global get_numbanks
get_numbanks:
	ldy	ROM_BANK	; make sure ROM bank 0
	stz	ROM_BANK
	ldx	#0		; clear high
	lda	$FF80		; special ROM build version byte
	sty	ROM_BANK	; restore previous bank
	bpl	1f		; branch if version negative
	dex			; decrement high for sign extend
1:	rts

