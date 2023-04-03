.include "imag.inc"
.text

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

;
; typedef struct { int x, y } graph_pos_t;
; void fb_graph_put_char(graph_pos_t *pos_ptr, unsigned char c);
;                                     rc2/3                  a
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_put_char
;
.global cx16_k_graph_put_char
cx16_k_graph_put_char:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	tax			; save c
				; r0 = pos_ptr->x
				; r1 = pos_ptr->y
	ldy	#4-1		; copy 4 bytes
copyposin:
	lda	(__rc2),y	; from pos_ptr
	sta	r0,y		; to r0 & r1
	dey
	bpl	copyposin
	ldy	__rc2		; save rc2/3
	phy
	ldy	__rc2+1
	phy
	txa			; a = c
	jsr	__GRAPH_PUT_CHAR
	ply
	sty	__rc2+1
	ply
	sty	__rc2
	ldy	#4-1		; copy 4 bytes
copyposout:
	lda	r0,y		; copy from r0 & r1
	sta	(__rc2),y	; to pos_ptr
	dey
	bpl	copyposout
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
