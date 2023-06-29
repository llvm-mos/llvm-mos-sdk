MEMORY {
	zp : ORIGIN = __rc31 + 1, LENGTH = 0xf820dc - (__rc31 + 1)
	console_ram (rw) : ORIGIN = 0xf82680, LENGTH = 0x4000 - 0x2680
}
