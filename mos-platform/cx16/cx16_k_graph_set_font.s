.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_set_font(void *fontaddr);
; llvm-mos:                        rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_set_font
;
.global cx16_k_graph_set_font
.section .text.cx16_k_graph_set_font,"ax",@progbits
cx16_k_graph_set_font:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
				; r0 = fontaddr (already present)
	jsr	__GRAPH_SET_FONT
	X16_kernal_pop_r6_r10
	rts
