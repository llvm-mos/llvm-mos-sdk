.include "imag.inc"
.include "cx16.inc"
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
; llvm-mos:                                    rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-graph_init
;
.global cx16_k_graph_init
cx16_k_graph_init:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
				; r0 = fb_vector_table (already set)
	jsr	__GRAPH_INIT
	X16_kernal_pop_r6_r10
	rts
