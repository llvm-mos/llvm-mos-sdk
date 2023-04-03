.include "imag.inc"
.text

;
; typedef struct { void *fb_init;
;		   void *fb_get_info;
;                  void *fb_set_palette;
;                  void *fb_cursor_position;
;	           void *fb_cursor_next_line;
;		   void *fb_get_pixel;
;                  void *fb_get_pixels;
;                  void *fb_set_pixel;
;                  void *fb_set_pixels;
;                  void *fb_set_8_pixels;
;                  void *fb_set_8_pixels_opaque;
;                  void *fb_fill_pixels;
;                  void *fb_filter_pixels;
;                  void *fb_move_pixels;
;                } graph_fb_functions_t;
; void cx16_k_graph_init(graph_fb_functions_t *fb_funcs_ptr);
;                                              rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_init
;
.global cx16_k_graph_init
cx16_k_graph_init:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2
	sty	r0		; r0 = fb_vector_table
	ldy	__rc2+1
	sty	r0+1
	jsr	__GRAPH_INIT
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
