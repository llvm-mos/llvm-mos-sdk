/* NES-MMC1 iNES file linker script. */

INCLUDE common.ld

/* Place C RAM sections in NES RAM. */
INCLUDE c-in-ram.ld

/**
 * Place C ROM sections in PRG-ROM bank 15, since it's assumed to be present at
 * 0xc000 at startup.
 */
REGION_ALIAS("c_rom", prg_rom_15)
REGION_ALIAS("c_rom_vma", prg_rom_hi)
