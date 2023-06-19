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
	lda #$ff ; bank 0 = 0xFF (I/O)
	tam #$01
	lda #$f8 ; bank 1 = 0xF8 (RAM)
	tam #$02
	lda #mos8(__start_bank_2)
	tam #$04
	lda #mos8(__start_bank_3)
	tam #$08
	lda #mos8(__start_bank_4)
	tam #$10
; TODO: We currently don't support fixed banks > 8KB, so these aren't
; currently necessary.
;	lda #mos8(__start_bank_5)
;	tam #$20
;	lda #mos8(__start_bank_6)
;	tam #$40
;	lda #mos8(__start_bank_7)
;	tam #$80

; Initialize stack pointer to 0xFF.
	tax
	txs
; Disable interrupts (MMIO).
	lda #$07
	sta $1402
