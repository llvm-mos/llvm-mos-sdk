INCLUDE pce-imag-regs.ld

INCLUDE ipl-cd-ram-banked-sections.ld
INCLUDE cd-memory.ld
REGION_ALIAS("c_ram", card_bank128)

__stack = 0x4000;
__mos_pce_cd_ipl = 1;

INCLUDE cd-sections.ld
