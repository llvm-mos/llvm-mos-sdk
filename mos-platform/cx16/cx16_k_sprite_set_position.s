.include "imag.inc"
.include "cx16.inc"
.text

; unsigned char cx16_k_sprite_set_position(unsigned char num, unsigned int xpos, unsigned int ypos); // returns 0 on success
;                                                        a                 x/rc2              rc3/4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-sprite_set_position
;
.global cx16_k_sprite_set_position
cx16_k_sprite_set_position:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
				; a = num
	stx	__r0		; __r0 = xpos
	ldy	__rc2
	sty	__r0+1
	ldy	__rc3
	sty	__r1		; __r1 = ypos
	ldy	__rc3+1
	sty	__r1+1
	jsr	__SPRITE_SET_POSITION
	lda	#0		; return 0 on success
	adc	#0		; return 1 on error (carry set)
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
