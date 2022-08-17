; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 0
; This defaults to CHR-ROM, but settings this to 0 gives CHR-RAM.
.weak __chr_rom_size
__chr_rom_size = 8

; This defaults to NROM-256, but setting this to 16 gives NROM-128.
.weak __prg_rom_size
__prg_rom_size = 32
