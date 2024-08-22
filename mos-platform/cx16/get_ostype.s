.include "imag.inc"
.include "cx16.inc"
.text

;
; signed char get_ostype(void);  // return ROM build version (negative pre-release, -1=custom)
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/get_ostype.s
;
.global get_ostype
.section .text.get_ostype,"axR",@progbits
get_ostype:
	ldy	rom_bank	; make sure ROM bank 0
	stz	rom_bank
	lda	$FF80		; special ROM build version byte
	sty	rom_bank	; restore previous bank
        rts

