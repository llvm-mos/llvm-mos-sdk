.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_clear(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_clear
;
.global cx16_k_graph_clear
cx16_k_graph_clear:
	jmp	__GRAPH_CLEAR
