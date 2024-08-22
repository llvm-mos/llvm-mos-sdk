.include "imag.inc"
.include "cx16.inc"
.text

;
; long cx16_k_graph_get_char_size(unsigned char c, unsigned char style); // if printable returns info (0x00bbwwhh), else negative style byte (0xFF0000ss)
; llvm-mos:                                     A                X
; X16-kernal:                                   A                X
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_get_char_size
;
.global cx16_k_graph_get_char_size
.section .text.cx16_k_graph_get_char_size,"axR",@progbits
cx16_k_graph_get_char_baseline:
	X16_kernal_push_r6_r10	; appears to trash additional registers
				; A = c (already set)
				; X = format (already set)
	jsr	__GRAPH_GET_CHAR_SIZE
	stz	__rc3		; upper byte 0
	bcc	1f		; branch if is printable char
	dec	__rc3		; upper byte $FF
	stz	__rc2
	tya			; set 0xFF0000ss style from Y
	ldx	#0
	rts
1:	sta	__rc2		; set 0x00bbxxxx baseline offset from A
	phx			; save width from X
	tya
	tax			; set 0x00xxhhxx height from Y
	pla			; set 0x00xxxxww width
	X16_kernal_pop_r6_r10
	rts
