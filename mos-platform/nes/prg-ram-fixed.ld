ASSERT(__prg_ram_size + __prg_nvram_size <= 8,
       "At most 8 KiB of PRG-(NV)RAM is supported.")

MEMORY {
  prg_ram : ORIGIN = 0x6000, LENGTH = (__prg_ram_size + __prg_nvram_size) * 1024
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram
}
