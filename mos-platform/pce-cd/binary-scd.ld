INCLUDE pce-imag-regs.ld

INCLUDE scd-ram-banked-sections.ld
INCLUDE cd-memory.ld
REGION_ALIAS("c_ram", card_bank104)

__stack = 0x4000;
__mos_pce_cd_binary = 1;

INCLUDE cd-sections.ld
