; xegs ROM size, only 32, 64, 128 and 256 are valid sizes (in KiB)

.weak __cart_rom_size
; default to 256K
__cart_rom_size = 256

; the default INIT (which can be overriden) selects bank 0; this is
; because on real hardware the bank selection is typically random
.text
.weak __cart_init
	.global _cart_init
_cart_init:
	lda #0
	sta $d500
	rts
