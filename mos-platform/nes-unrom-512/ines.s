; Settings in the iNES 2.0 header.

.global __mapper
__mapper = 30

; Most UNROM-512 developers assume the board to not have bus conflicts.
; We have only partial support for avoiding bus conflicts, so enable the
; "self-flashable" (no bus conflicts) board variant by default.
;
; See https://www.nesdev.org/wiki/Bus_conflict for more information.
.weak __battery
__battery = 1

; UNROM-512 boards come with CHR-RAM by default.
; Setting this to 0 gives CHR-ROM.
.weak __chr_ram_size
__chr_ram_size = 32
.weak __chr_rom_size
__chr_rom_size = 0
