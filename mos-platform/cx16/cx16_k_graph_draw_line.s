.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
;                                         a/x            rc2/3            rc4/5            rc6/7
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_draw_line
;
.global cx16_k_graph_draw_line
cx16_k_graph_draw_line:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = x1
	stx	__r0+1
				; __r1 = y1 (already set)
				; __r2 = x2 (already set)
				; __r3 = y2 (already set)
	jsr	__GRAPH_DRAW_LINE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
