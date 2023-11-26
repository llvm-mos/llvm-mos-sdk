; xegs ROM size, only 32, 64, 128 and 256 are valid sizes (in KiB)

.weak __cart_rom_size
; default to 256K
__cart_rom_size = 256

; explicitly select bank 0, allows for override of INIT
.text
	.global _cart_init
_cart_init:
	lda #0
	sta $d500
	rts
