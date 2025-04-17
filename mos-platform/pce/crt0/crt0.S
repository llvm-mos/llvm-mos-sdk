; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https:;github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

; This section must never grow larger than ~7.9KB, as it must fit entirely
; in the first bank, including reserved bytes for IRQ vectors.
.section .early_start,"axR",@progbits
.global _early_start
_early_start:
; Disable interrupts (CPU).
	sei
; Set CPU speed to high (7.16MHz).
	csh
; Configure default banking layout:
	lda #$ff ; bank 0 = 0xFF (I/O)
	tam #$01
; Initialize stack pointer to 0xFF.
	tax
	txs
	lda #$f8 ; bank 1 = 0xF8 (RAM)
	tam #$02
	lda #__start_bank_2
	tam #$04
	lda #__start_bank_3
	tam #$08
	lda #__start_bank_4
	tam #$10
	lda #__start_bank_5
	tam #$20
	lda #__start_bank_6
	tam #$40
; Jump to the real start routine, now that banks are set up.
	jmp _start

.section .init.50,"ax",@progbits
; Disable interrupts (MMIO).
	lda #$07
	sta $1402
; Reset the VDC, VCE and PSG.
	jsr __pce_vdc_init
	jsr __pce_psg_init
