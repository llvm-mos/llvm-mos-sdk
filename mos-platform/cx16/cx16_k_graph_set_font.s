.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_graph_set_font(void *fontaddr);
;                                  rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_set_font
;
.global cx16_k_graph_set_font
cx16_k_graph_set_font:
	save_X16_scratch
				; r0 = fontaddr (already present)
	jsr	__GRAPH_SET_FONT
	restore_X16_scratch
	rts
