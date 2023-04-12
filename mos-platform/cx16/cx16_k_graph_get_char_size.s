.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_graph_get_char_size(unsigned char c, unsigned char style); // if printable returns info (0x00bbwwhh), else negative style byte (0xFF0000ss)
;                                               a                x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_get_char_size
;
.global cx16_k_graph_get_char_size
cx16_k_graph_get_char_baseline:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
				; a = c (already set)
				; x = format (already set)
	jsr	__GRAPH_GET_CHAR_SIZE
	stz	__rc3		; upper byte 0
	bcc	isprintchar
	dec	__rc3		; upper byte $FF
	stz	__rc2
	txa			; return style
	ldx	#0
	bra	return
isprintchar:
	sta	__rc2		; return baseline offset
	tya
	tax			; return width
	txa			; return height
return:
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
