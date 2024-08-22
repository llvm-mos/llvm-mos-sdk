.include "imag.inc"
.include "cx16.inc"
.text

;
; typedef struct { int x, y; } mouse_pos_t;
; unsigned char cx16_k_mouse_get(mouse_pos_t *mouse_pos_ptr);	// returns mouse button byte
; llvm-mos:                                   rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-mouse_get
;
.global cx16_k_mouse_get
.section .text.cx16_k_mouse_get,"axR",@progbits
cx16_k_mouse_get:
	ldx	#__r4		; x = temp pos
	jsr	__MOUSE_GET
	tax			; save buttons
	ldy	#4-1		; copy 4 byte pos to xy_ptr
1:	lda	__r4,y
	sta	(__rc2),y
	dey
	bpl	1b
	txa			; return buttons
	rts
