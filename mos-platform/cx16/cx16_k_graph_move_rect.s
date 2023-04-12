.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_move_rect(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int width, unsigned int height);
;                                         a/x            rc2/3            rc4/5            rc6/7               rc8/9               rc10/11
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_move_rect
;
.global cx16_k_graph_move_rect
cx16_k_graph_move_rect:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = sx
	stx	__r0+1
				; __r1 = sy (already set)
				; __r2 = tx (already set)
				; __r3 = ty (already set)
				; __r4 = width (already set)
				; __r5 = height (already set)
	jsr	__GRAPH_MOVE_RECT
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
