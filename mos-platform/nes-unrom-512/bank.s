; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "imag.inc"

.section .text._bank,"ax",@progbits
.global _BANK
_BANK: .byte $FF

.zeropage _BANK_SHADOW

.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
	lda __rc20
	pha

	; adjust PRG bank
	sta __rc17 ; __rc17 = requested PRG bank
	lda _BANK_SHADOW
	and #$1F
	sta __rc20 ; __rc20 = previous PRG bank (saved)
	lda _BANK_SHADOW
	and #$70
	ora __rc17
	sta _BANK ; stored: new bank shadow value
	sta _BANK_SHADOW

	; perform indirect call
	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir

	; restore PRG bank
	lda _BANK_SHADOW
	and #$70
	ora __rc20
	sta _BANK ; stored: previous bank shadow value
	sta _BANK_SHADOW

	pla
	sta __rc20
	rts
