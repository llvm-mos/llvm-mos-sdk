/* Place C sections in PRG-RAM bank 0. */
REGION_ALIAS("c_ram_vma", prg_ram_0_vma)
REGION_ALIAS("c_ram_lma", prg_ram_0_lma)

/* Ensure that PRG-RAM bank 0 is selected before C starts. */
INPUT(init-prg-ram-0.o)
