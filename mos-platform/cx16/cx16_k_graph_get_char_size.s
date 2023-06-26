.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_graph_get_char_size(unsigned char c, unsigned char style); // if printable returns info (0x00bbwwhh), else negative style byte (0xFF0000ss)
; llvm-mos:                                     A                X
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_get_char_size
; NOTE: As of x16-rom r43 modifies r10, r11, r12 & r13
;
.global cx16_k_graph_get_char_size
cx16_k_graph_get_char_baseline:
	save_X16_scratch
				; A = c (already set)
				; X = format (already set)
	jsr	__GRAPH_GET_CHAR_SIZE
	stz	__rc3		; upper byte 0
	bcc	1f		; branch if is printable char
	dec	__rc3		; upper byte $FF
	stz	__rc2
	tya			; set 0xFF0000ss style from Y
	ldx	#0
	bra	2f
1:	sta	__rc2		; set 0x00bbxxxx baseline offset from A
	phx			; save width from X
	tya
	tax			; set 0x00xxhhxx height from Y
	pla			; set 0x00xxxxww width
2:	restore_X16_scratch
	rts
