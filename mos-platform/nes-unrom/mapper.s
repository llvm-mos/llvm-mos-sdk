; Copyright 2022, 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "imag.inc"

.zeropage _BANK_SHADOW

.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
    tay
	lda _BANK_SHADOW
	pha
	tya
	jsr set_prg_bank
	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir
	pla
	jmp set_prg_bank
