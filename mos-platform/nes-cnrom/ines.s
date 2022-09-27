; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 3
; This defaults to CHR-ROM, but settings this to 0 gives CHR-RAM.
.weak __chr_rom_size
__chr_rom_size = 2048

.weak __prg_rom_size
__prg_rom_size = 32
