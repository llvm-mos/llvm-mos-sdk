.include "imag.inc"
.include "cx16.inc"
.text

; unsigned char cx16_k_sprite_set_position(unsigned char num, unsigned int xpos, unsigned int ypos); // returns 0 on success
; llvm-mos:                                              A                 X/rc2              rc3/4
; llvm-mos aliases:                                      A                 r0L/X              r0H/r1L
; X16 kernal:                                            A                 r0		      r1
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-sprite_set_position
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_sprite_set_position
cx16_k_sprite_set_position:
	sta	__r4		; save num in r4 temp
	lda	__rc2
	ldy	__rc3
	stx 	__r0		; r0 = xpos
	sta	__r0+1
	sty	__r1		; r1 = ypos
	ldy	__rc3+1
	sty	__r1+1
	lda	__r4		; A = num (restored from temp)
	jsr	__SPRITE_SET_POSITION
	lda	#0		; return 0 on success
	adc	#0		; return 1 on error (carry set)
	rts
