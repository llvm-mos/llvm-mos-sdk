/* Place C sections in PRG-RAM bank 0. */
REGION_ALIAS("c_ram", prg_ram_0)

/* Ensure that PRG-RAM bank 0 is selected before C starts. */
INPUT(init-prg-ram-0.o)

__stack = 0x7fff;
