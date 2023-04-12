.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_clear(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_clear
;
.global cx16_k_graph_clear
cx16_k_graph_clear:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	jsr	__GRAPH_CLEAR
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
