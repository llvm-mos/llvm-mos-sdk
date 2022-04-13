; Defaults for settings in the iNES 2.0 header.

/* Note that the "size" fields all have wildly different interpretations; see the
 * reference above for details. */
.weak __prg_ram_size
__prg_ram_size = 0
.weak __prg_nvram_size
__prg_nvram_size = 0
.weak __chr_ram_size
__chr_ram_size  = 0
.weak __chr_nvram_size
__chr_nvram_size = 0

.weak __mirroring
__mirroring = 0
.weak __battery
__battery = 0
.weak __trainer
__trainer = 0
.weak __four_screen
__four_screen = 0
.weak __submapper
__submapper = 0

.weak __console_type
__console_type = 0
.weak __timing
__timing = 0
.weak __ppu_type
__ppu_type = 0
.weak __hw_type
__hw_type = 0
.weak __extended_console_type
__extended_console_type = 0

.weak __misc_roms
__misc_roms = 0
.weak __default_expansion_device
__default_expansion_device = 0
