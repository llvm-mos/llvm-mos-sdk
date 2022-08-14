; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 1

; Supports between 32 KiB and 512 KiB of PRG-ROM.
; Default to 256 KiB of PRG-ROM, since 512 KiB limits CHR-ROM to 64 KiB.
.weak __prg_rom_size
__prg_rom_size = 16

; Supports up to 128 KiB of CHR-ROM.
.weak __chr_rom_size
__chr_rom_size = 16
