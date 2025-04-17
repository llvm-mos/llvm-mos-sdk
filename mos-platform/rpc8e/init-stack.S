; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

; Initialize the soft stack by dynamically figuring out the available memory.

.global __do_init_stack
.section .init.100,"ax",@progbits
__do_init_stack:
	rep #$30 ; 16-bit index, 16-bit accumulator

	ldy #$a55a
	ldx #$fffe
; This loop is guaranteed to end at 0x1FFE.
.Lloop:
	; Set memory end pointer (0x?FFE) to 0xA55A, compare.
	lda $00,x
	pha
	tya
	sta $00,x
	cmp $00,x
	beq .Lfound

	pla
	sta $00,x
	txa

	; Memory not found; subtract 0x2000 from pointer.
	sec
	sbc #$2000
	tax
	bra .Lloop
.Lfound:
	pla
	sta $00,x
	txa
	inc a
	inc a
	sta __rc0

	sep #$30 ; Back to 8-bit mode
