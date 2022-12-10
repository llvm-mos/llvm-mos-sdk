; defaults

; ROM size, only 8 and 16 KiB are supported
.weak __cart_rom_size
__cart_rom_size = 8

; INIT typically isn't used but allow override
.weak _cart_init
_cart_init:
	rts
