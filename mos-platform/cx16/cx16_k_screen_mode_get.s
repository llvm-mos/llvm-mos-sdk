.include "imag.inc"
.include "cx16.inc"
.text

;
; typedef struct { unsigned char mode, columns, rows; } screen_mode_info_t;
; unsigned char cx16_k_screen_mode_get(screen_mode_info_t *info_ptr); // returns 0 on success
; llvm-mos:                                                rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-screen_mode
;
.global cx16_k_screen_mode_get
cx16_k_screen_mode_get:
	sec			; C = set for get screen mode info
	jsr	__SCREEN_MODE
	sty	__r4		; save tile_h
	ldy	#0
	sta	(__rc2),y	; store mode
	iny
	txa
	sta	(__rc2),y	; store columns
	iny
	lda	__r4
	sta	(__rc2),y	; store rows
	rts
