; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 2

; We have only partial support for avoiding bus conflicts,
; For modern emulators, assume no bus conflicts.
.weak __submapper
__submapper = 1

; This defaults to CHR-ROM, but settings this to 0 gives CHR-RAM.
.weak __chr_rom_size
__chr_rom_size = 8
