;
; Copyright (c) 2023 Adrian "asie" Siekierka
;
; This software is provided 'as-is', without any express or implied
; warranty. In no event will the authors be held liable for any damages
; arising from the use of this software.
;
; Permission is granted to anyone to use this software for any purpose,
; including commercial applications, and to alter it and redistribute it
; freely, subject to the following restrictions:
;
; 1. The origin of this software must not be misrepresented; you must not
;    claim that you wrote the original software. If you use this software
;    in a product, an acknowledgment in the product documentation would be
;    appreciated but is not required.
;
; 2. Altered source versions must be plainly marked as such, and must not be
;    misrepresented as being the original software.
;
; 3. This notice may not be removed or altered from any source distribution.
;

.include "imag.inc"

.section .init.50,"axR",@progbits
; Clear emulation mode.
	clc
	xce
; Initialize hardware stack pointer to 0x01FF.
; RedPower 2 has a bug where the stack pointer is set to 0x0200 on boot, so
; an 8-bit-only TXS would have set it to 0x02FF, not 0x01FF.
	rep #$30
	ldx #$01FF
	txs
; Work in 8-bit native mode.
	sep #$30
; Clear decimal mode.
	cld
; Enable RedBus by default.
	mmu #$02
; Use the display device by default.
; Changing the active device takes 1 world tick (0.05 seconds), but only if
; the device is actually different; for common printf/getchar calls, we'd
; like to avoid doing so.
	lda $01 ; boot_display_id
	mmu #$00
