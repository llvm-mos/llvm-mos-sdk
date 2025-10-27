INPUT(reset.o)

ASSERT(__prg_ram_size <= 32,
       "At most 32 KiB of PRG-RAM is supported.")

MEMORY {
  prg_ram : ORIGIN = 0x6000, LENGTH = (__prg_ram_size * 1024) - 10
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram
}

/* TODO: Is this really needed? */
REGION_ALIAS("c_readonly", prg_ram)

OUTPUT_FORMAT {
  TRIM(prg_ram)
}
