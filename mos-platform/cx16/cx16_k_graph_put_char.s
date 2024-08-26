.include "imag.inc"
.include "cx16.inc"
.text

;
; typedef struct { int x, y } graph_pos_t;
; void cx16_k_graph_put_char(graph_pos_t *pos_ptr, unsigned char c);
; llvm-mos:                               rc2/3                  A
; llvm-mos aliases:                       r0                     A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_put_char
;
.global cx16_k_graph_put_char
.section .text.cx16_k_graph_put_char,"axR",@progbits
cx16_k_graph_put_char:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	ldy	__rc2		; push rc2/3
	sty	__r4
	phy
	ldy	__rc2+1
	sty	__r4+1
	phy
	tax			; save c
	ldy	#4-1		; copy 4 bytes
1:	lda	(__r4),y	; from pos_ptr x, y
	sta	__r0,y		; to r0 & r1
	dey
	bpl	1b
	txa			; A = c
	jsr	__GRAPH_PUT_CHAR
	ply
	sty	__r4+1
	ply
	sty	__r4
	ldy	#4-1		; copy 4 bytes
2:	lda	__r0,y		; from r0 & r1
	sta	(__r4),y	; to pos_ptr x, y
	dey
	bpl	2b
	X16_kernal_pop_r6_r10
	rts
