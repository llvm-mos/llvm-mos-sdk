; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 111

; GTROM boards come with CHR-RAM by default.
.weak __chr_ram_size
__chr_ram_size = 16

.globl __chr_rom_size
__chr_rom_size = 0
