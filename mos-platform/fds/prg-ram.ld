INPUT(reset.o)

MEMORY {
  prg_ram : ORIGIN = 0x6000, LENGTH = (32 * 1024) - 10
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram
}

REGION_ALIAS("c_readonly", prg_ram)

OUTPUT_FORMAT {
  TRIM(prg_ram)
}
