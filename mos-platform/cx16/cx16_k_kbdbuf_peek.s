.include "imag.inc"
.include "cx16.inc"
.text

;
; int cx16_k_kbdbuf_peek(unsigned char *index_ptr); // returns negative if empty, if non-NULL contents of index set to queue length
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-kbdbuf_peek
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_kbdbuf_peek
cx16_k_kbdbuf_peek:
	jsr	__KBDBUF_PEEK
	tay			; save (possible) char
	lda	__rc2
	ora	__rc2+1
	beq	1f		; branch if index_ptr NULL
	txa
	sta	(__rc2)		; set *index_ptr to queue len
1:	txa			; test queue len
	beq	2f		; branch if queue empty
	ldx	#0
	tya			; restore char
	rts			; return char
2:	ldx	#$ff		; return -1 for empty
	txa
	rts
