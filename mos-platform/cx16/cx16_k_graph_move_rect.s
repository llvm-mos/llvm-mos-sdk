.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_move_rect(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int width, unsigned int height);
; llvm-mos                                A/X            rc2/3            rc4/5            rc6/7               r8/9                rc10/11
; llvm-mos aliases:                       A/X            r0               r1               r2                  r3                  r4
; X16 kernal:                              r0            r1               r2               r3                  r4                  r5
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_move_rect
;
.global cx16_k_graph_move_rect
.section .text.cx16_k_graph_move_rect,"axR",@progbits
cx16_k_graph_move_rect:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	ldy	__rc10		; NOTE: copy args backwards due to overlap
	sty	__r5		; r5 = height
	ldy	__rc10+1
	sty	__r5+1
	ldy	__rc8
	sty	__r4		; r4 = width
	ldy	__rc8+1
	sty	__r4+1
	ldy	__rc6
	sty	__r3		; r3 = ty
	ldy	__rc6+1
	sty	__r3+1
	ldy	__rc4
	sty	__r2		; r2 = tx
	ldy	__rc4+1
	sty	__r2+1
	ldy	__rc2
	sty	__r1		; r1 = y
	ldy	__rc2+1
	sty	__r1+1
	sta	__r0		; r0 = x
	stx	__r0+1
	jsr	__GRAPH_MOVE_RECT
	X16_kernal_pop_r6_r10
	rts
