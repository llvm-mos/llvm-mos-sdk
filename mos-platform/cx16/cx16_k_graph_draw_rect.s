.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int corner_radius, unsigned char fillflag);
; llvm-mos                               A/X           rc2/3               rc4/5               rc6/7                 r8/9                        rc10
; llvm-mos aliases:                      A/X           r0                  r1                  r2                    r3                          r4L
; X16 kernal:                             r0           r1                  r2                  r3                    r4                          C
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_draw_rect
;
.global cx16_k_graph_draw_rect
.section .text.cx16_k_graph_draw_rect,"ax",@progbits
cx16_k_graph_draw_rect:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	ldy	__rc10		; load fillflag
	cpy	#1		; C = set if fillflag >= 1
	ldy	__rc8		; NOTE: copy args backwards due to overlap
	sty	__r4		; r4 = corner_radius
	ldy	__rc8+1
	sty	__r4+1
	ldy	__rc6
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
	jsr	__GRAPH_DRAW_RECT
	X16_kernal_pop_r6_r10
	rts
