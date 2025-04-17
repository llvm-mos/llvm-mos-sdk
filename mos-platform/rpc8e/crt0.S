; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

.section .init.50,"ax",@progbits
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
