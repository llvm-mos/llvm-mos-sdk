; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 28

; Supports up to 32 KiB of CHR-RAM.
.weak __chr_rom_size
__chr_rom_size = 0
.weak __chr_ram_size
__chr_ram_size = 32
