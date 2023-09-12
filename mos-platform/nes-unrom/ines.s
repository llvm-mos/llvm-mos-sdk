; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 2

; This defaults to CHR-ROM, but settings this to 0 gives CHR-RAM.
.weak __chr_rom_size
__chr_rom_size = 8
