INCLUDE pce-imag-regs.ld

INCLUDE scd-ram-banked-sections.ld
INCLUDE cd-memory.ld
REGION_ALIAS("c_ram", card_bank104)

INCLUDE cd-sections.ld
