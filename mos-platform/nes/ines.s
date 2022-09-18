; Defaults for settings in the iNES 2.0 header.

/* All non-raw size fields are given in units of KiB (1024 bytes) */
.weak __prg_ram_size
__prg_ram_size = 0
.weak __prg_nvram_size
__prg_nvram_size = 0
.weak __chr_ram_size
__chr_ram_size = 0
.weak __chr_nvram_size
__chr_nvram_size = 0

/* Raw setting for RAM size header fields. */
.weak __prg_ram_size_raw
__prg_ram_size_raw = 0
.weak __prg_nvram_size_raw
__prg_nvram_size_raw = 0
.weak __chr_ram_size_raw
__chr_ram_size_raw = 0
.weak __chr_nvram_size_raw
__chr_nvram_size_raw = 0

/**
 * Raw setting for ROM size header fields. The least significant byte is placed
 * at offset 4 or 5, and the most significant nibble at offset 9. This also
 * allows using the exponent/multiplier mode. Only the lowest 24 bits are
 * significant.
 */
.weak __prg_rom_size_raw
__prg_rom_size_raw = 0
.weak __chr_rom_size_raw
__chr_rom_size_raw = 0

; Default to vertical mirroring (horizontal scrolling).
.weak __mirroring
__mirroring = 1
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
