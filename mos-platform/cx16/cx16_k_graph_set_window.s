.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_set_window(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
;                                         a/x           rc2/3               rc4/5               rc6/7
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_set_window
;
.global cx16_k_graph_set_window
cx16_k_graph_set_window:
	save_X16_scratch
	ldy	__rc6		; NOTE: copy args backwards due to overlap
	sty	__r3		; r3 = height
	ldy	__rc6+1
	sty	__r3+1
	ldy	__rc4
	sty	__r2		; r2 = width
	ldy	__rc4+1
	sty	__r2+1
	ldy	__rc2
	sty	__r1		; r3 = y
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; r0 = x
	stx	__r0+1
	jsr	__GRAPH_SET_WINDOW
	restore_X16_scratch
	rts
