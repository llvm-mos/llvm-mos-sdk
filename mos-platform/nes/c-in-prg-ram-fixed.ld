/* Place C sections in PRG-RAM. */
REGION_ALIAS("c_ram", prg_ram)

__stack = ORIGIN(prg_ram) + LENGTH(prg_ram) - 1;
