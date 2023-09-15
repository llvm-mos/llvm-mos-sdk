; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "imag.inc"

.zeropage _BANK_SHADOW

.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
	sta __rc17 ; __rc17 = requested PRG bank
	
	lda __rc20
	pha

	; adjust PRG bank
	lda _BANK_SHADOW
	and #$1F
	sta __rc20 ; __rc20 = previous PRG bank (saved)
	lda _BANK_SHADOW
	and #$E0
	ora __rc17
	sta _BANK_SHADOW
	tay
	sta __rom_poke_table,y

	; perform indirect call
	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir

	; restore PRG bank
	lda _BANK_SHADOW
	and #$E0
	ora __rc20
	tay
	pla
	sta __rc20
	tya
	
	jmp set_bank_state
