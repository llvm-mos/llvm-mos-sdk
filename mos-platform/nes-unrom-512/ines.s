; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 30

; UNROM-512 boards come with CHR-RAM by default.
; Setting this to 0 gives CHR-ROM.
.weak __chr_ram_size
__chr_ram_size = 32
.weak __chr_rom_size
__chr_rom_size = 0
