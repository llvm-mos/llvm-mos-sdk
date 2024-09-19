.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned short get_numbanks(void); // return number of 8K RAM banks at 0xA000-0xBFFF (64=512K up to 256=2MB)
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/get_numbanks.s
;
.global get_numbanks
.section .text.get_numbanks,"ax",@progbits
get_numbanks:
	sec		; set carry to get MEMTOP
	jsr	__MEMTOP
	ldx	#0	; assume < 256
	cmp	#0	; is it 0? (means 256)
	bne	1f	; branch if not
	inx		; increment high for 256 ($0100)
1:	rts

