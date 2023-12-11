; libretro Mesen has a bug that causes it to crash unless battery is enabled.

; See the following:
; https://github.com/SourMesen/Mesen/blob/86326e832974d984846ae078e568c023a5f76f1f/Libretro/libretro.cpp#L1051
;   This issues a state save upon initialization.
; https://github.com/SourMesen/Mesen/blob/86326e832974d984846ae078e568c023a5f76f1f/Core/UnRom512.h#L51
;   This initializes a copy of the original PRG ROM, but only if battery.
; https://github.com/SourMesen/Mesen/blob/86326e832974d984846ae078e568c023a5f76f1f/Core/UnRom512.h#L67
;   This runs during a state save, but it depends on the PRG ROM copy

; This appears to already have been fixed in Mesen2, but not in MesenX. We
; should switch to it as soon as there is a libretro core available.

.globl __battery
__battery = 1
