.include "imag.inc"

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

.text

; unsigned char cx16_k_sprite_set_position(unsigned char num, unsigned int xpos, unsigned int ypos); // returns 0 on success
;                                                        a                 x/rc2              rc3/4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-sprite_set_position
;
.global cx16_k_sprite_set_position
cx16_k_sprite_set_position:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
				; a = num
	stx	r0		; r0 = xpos
	ldy	__rc2
	sty	r0+1
	ldy	__rc3
	sty	r1		; r1 = ypos
	ldy	__rc3+1
	sty	r1+1
	jsr	__SPRITE_SET_POSITION
	lda	#0		; return 0 on success
	adc	#0		; return 1 on error (carry set)
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
