; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https:;github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

; Hardware initialization.

.section .init.50,"axR",@progbits
; Disable interrupts (CPU).
	sei
; Set CPU speed to high (7.16MHz).
	csh
; Configure default banking layout:
; bank 0 = 0xFF (I/O)
; bank 1 = 0xF8 (RAM)
	lda #$f8
	tam #$02
	lda #$ff
	tam #$01
; Initialize stack pointer to 0xFF.
	tax
	txs
; Disable interrupts (MMIO).
	lda #$07
	sta $1402
