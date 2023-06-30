PROVIDE(__pce_cdb_use_psg = 0);
PROVIDE(__pce_cdb_use_graphics = 0);

PROVIDE(__pce_zp_end = __pce_cdb_use_graphics > 0 ? 0x20dc : (__pce_cdb_use_psg > 0 ? 0x20e6 : 0x20ec));
PROVIDE(__pce_ram_start = __pce_cdb_use_graphics > 0 ? 0x2649 : (__pce_cdb_use_psg > 0 ? 0x2616 : 0x22d0));
PROVIDE(__pce_ram_end = 0x4000);

MEMORY {
	zp : ORIGIN = __rc31 + 1, LENGTH = (0xf80000 + __pce_zp_end) - (__rc31 + 1)
	console_ram (rw) : ORIGIN = (0xf80000 + __pce_ram_start), LENGTH = __pce_ram_end - __pce_ram_start
}

__stack = __pce_ram_end;
