.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_clear(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_clear
;
.global cx16_k_graph_clear
.section .text.cx16_k_graph_clear,"axR",@progbits
cx16_k_graph_clear:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	jsr	__GRAPH_CLEAR
	X16_kernal_pop_r6_r10
	rts

