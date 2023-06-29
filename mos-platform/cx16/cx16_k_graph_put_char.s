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
cx16_k_graph_put_char:
	X16_pushw __r6		; paranoid about trashing r6
	ldy	__rc2		; copy rc2/3 to r4 temp
	sty	__r4
	ldy	__rc2+1
	sty	__r4+1
	tax			; save c
	ldy	#4-1		; copy 4 bytes
1:	lda	(__r4),y	; from pos_ptr x, y
	sta	__r0,y		; to r0 & r1
	dey
	bpl	1b
	txa			; A = c
	jsr	__GRAPH_PUT_CHAR
	ldy	#4-1		; copy 4 bytes
2:	lda	__r0,y		; from r0 & r1
	sta	(__r4),y	; to pos_ptr x, y
	dey
	bpl	2b
	X16_popw __r6
	rts
