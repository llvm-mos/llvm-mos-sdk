.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_set_colors(unsigned char stroke, unsigned char fill, unsigned char background);
; llvm-mos:                                  A                     X                   rc2
; X16-kernal:                                A                     X                   Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_set_colors
;
.global cx16_k_graph_set_colors
cx16_k_graph_set_colors:
				; A = stroke (already set)
				; X = fill (already set)
	ldy	__rc2		; Y = background
	jmp	__GRAPH_SET_COLORS
