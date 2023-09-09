INCLUDE pce-imag-regs.ld

INCLUDE cd-ram-banked-sections.ld
INCLUDE cd-memory.ld
REGION_ALIAS("c_writeable", ram_bank128)

INCLUDE cd-sections.ld
