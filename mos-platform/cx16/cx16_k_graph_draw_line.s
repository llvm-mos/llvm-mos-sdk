.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
; llvm-mos                                A/X            rc2/3            rc4/5            rc6/7
; llvm-mos aliases:                       A/X            r0               r1               r2
; X16 kernal:                             r0             r1               r2               r3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_draw_line
;
.global cx16_k_graph_draw_line
.section .text.cx16_k_graph_draw_line,"axR",@progbits
cx16_k_graph_draw_line:
	X16_kernal_push_r6_r10	; documented as trashing additional regs
	ldy	__rc6		; NOTE: copy args backwards due to overlap
	sty	__r3		; __r3 = y2
	ldy	__rc6+1
	sty	__r3+1
	ldy	__rc4
	sty	__r2		; __r2 = x2
	ldy	__rc4+1
	sty	__r2+1
	ldy	__rc2
	sty	__r1		; __r1 = y1
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; __r0 = x1
	stx	__r0+1
	jsr	__GRAPH_DRAW_LINE
	X16_kernal_pop_r6_r10
	rts
