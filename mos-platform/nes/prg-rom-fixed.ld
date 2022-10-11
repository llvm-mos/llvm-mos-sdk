/* Common elements of NES-NROM iNES file linker scripts. */

ASSERT(__prg_rom_size == 16 || __prg_rom_size == 32,
       "NROM only supports 16 KiB or 32 KiB of PRG-ROM")

MEMORY {
  prg_rom_vma (rx) : ORIGIN = __prg_rom_size == 32 ? 0x8000 : 0xC000,
                     LENGTH = __prg_rom_size * 1024
}

REGION_ALIAS("c_rom_vma", prg_rom_vma)
REGION_ALIAS("c_rom_lma", prg_rom)

SECTIONS {
  .vector 0xfffa - ORIGIN(prg_rom_vma) + ORIGIN(prg_rom) : {
    SHORT(nmi) SHORT(_start) SHORT(irq)
  } >prg_rom
}
