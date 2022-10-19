REGION_ALIAS("c_rom_vma", prg_rom_vma)
REGION_ALIAS("c_rom_lma", prg_rom)

INCLUDE dpcm.ld

SECTIONS {
  .vector 0xfffa - ORIGIN(prg_rom_vma) + ORIGIN(prg_rom) : {
    SHORT(nmi) SHORT(_start) SHORT(irq)
  } >prg_rom
}
