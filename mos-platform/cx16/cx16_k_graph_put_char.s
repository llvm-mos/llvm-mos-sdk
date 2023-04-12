.include "imag.inc"
.include "cx16.inc"
.text

;
; typedef struct { int x, y } graph_pos_t;
; void cx16_k_graph_put_char(graph_pos_t *pos_ptr, unsigned char c);
;                                         rc2/3                  a
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_put_char
;
.global cx16_k_graph_put_char
cx16_k_graph_put_char:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; save rc2/3
	sty	__rc18		; to rc18/19
	ldy	__rc3
	sty	__rc19
	tax			; save c
				; __r0 = pos_ptr->x
				; __r1 = pos_ptr->y
	ldy	#4-1		; copy 4 bytes
copyposin:
	lda	(__rc18),y	; from pos_ptr
	sta	__r0,y		; to __r0 & __r1
	dey
	bpl	copyposin
	txa			; a = c
	jsr	__GRAPH_PUT_CHAR
	ldy	#4-1		; copy 4 bytes
copyposout:
	lda	__r0,y		; copy from __r0 & __r1
	sta	(__rc18),y	; to pos_ptr
	dey
	bpl	copyposout
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
