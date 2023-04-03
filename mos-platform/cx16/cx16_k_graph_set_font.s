.include "imag.inc"
.text

;
; void cx16_k_graph_set_font(void *fontaddr);
;                                  rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_set_font
;
.global cx16_k_graph_set_font
cx16_k_graph_set_font:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; r0 = fontaddr
	sty	r0
	ldy	__rc2+1
	sty	r0+1
	jsr	__GRAPH_SET_FONT
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
