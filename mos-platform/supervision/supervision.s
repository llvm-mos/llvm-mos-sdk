; Copyright 2022, 2023, 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "imag.inc"

.zeropage __sys_control

.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
	asl
	asl
	asl
	asl
	asl
	sta __rc18
	lda __sys_control
	and #$E0
	tay
	lda __sys_control
	and #$1F
	ora __rc18
	sta __sys_control
	sta 0x2026

	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir

	lda __sys_control
	and #$1F
	sty __rc2
	ora __rc2
	sta __sys_control
	sta 0x2026

	rts
