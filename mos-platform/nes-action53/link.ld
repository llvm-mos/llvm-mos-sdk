INCLUDE common.ld
INCLUDE prg-rom.ld
INCLUDE c-in-ram.ld

/* When changing mirroring mode, the rom size needs to be written to the
 * along with the banking configuration. If you need a custom banking setup
 * such as banking $c000 then you can override this value to change that
 */
PROVIDE(__supervisor_outer_bank = (__prg_rom_size >> 2) | 0x0c);
