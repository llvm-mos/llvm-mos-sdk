
; the default INIT (which can be overriden) selects bank 0; this is
; because on real hardware the XEGS bank selection is random
.text
.weak _cart_init
_cart_init:
	lda #0
	sta $d500
	rts
