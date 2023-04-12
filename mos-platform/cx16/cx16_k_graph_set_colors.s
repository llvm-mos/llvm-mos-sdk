.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_set_colors(unsigned char stroke, unsigned char fill, unsigned char background);
;                                        a                     x                   rc2
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_set_colors
;
.global cx16_k_graph_set_colors
cx16_k_graph_set_colors:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
				; a = stroke (already set)
				; x = fill (already set)
	ldy	__rc2		; y = background
	jsr	__GRAPH_SET_COLORS
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
