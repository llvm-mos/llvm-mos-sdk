.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_draw_image(unsigned int x, unsigned int y, void *imageaddr, unsigned int width, unsigned int height);
;                                         a/x           rc2/3        rc4/5                   rc6/7               rc8/9
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_draw_image
;
.global cx16_k_graph_draw_image
cx16_k_graph_draw_image:
	save_X16_scratch
	ldy	__rc8		; NOTE: copy args backwards due to overlap
	sty	__r4		; r4 = height
	ldy	__rc8+1
	sty	__r4+1
	ldy	__rc6
	sty	__r3		; r3 = width
	ldy	__rc6+1
	sty	__r3+1
	ldy	__rc4
	sty	__r2		; r2 = ptr
	ldy	__rc4+1
	sty	__r2+1
	ldy	__rc2
	sty	__r1		; r3 = y
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; r0 = x
	stx	__r0+1
	jsr	__GRAPH_DRAW_IMAGE
	restore_X16_scratch
	rts
