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
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0 = x
	stx	__r0+1
				; __r1 = y (already set)
				; __r2 = imageaddr (already set)
				; __r3 = width (already set)
				; __r4 = height (already set)
	jsr	__GRAPH_DRAW_IMAGE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
