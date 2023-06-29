INCLUDE pce-imag-regs.ld

INCLUDE ipl-cd-ram-banked-sections.ld
MEMORY {
	zp : ORIGIN = __rc31 + 1, LENGTH = 0xf820dc - (__rc31 + 1)
	console_ram (rw) : ORIGIN = 0xf83090, LENGTH = 0x4000 - 0x3090
}

REGION_ALIAS("c_ram", console_ram)

__stack = 0x4000;
__mos_pce_cd_ipl = 1;

INCLUDE cd-sections.ld
