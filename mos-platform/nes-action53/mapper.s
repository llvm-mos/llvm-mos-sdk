; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.
;
; Copyright 2019 Doug Fraker
; Copyright 2018 Christopher Parker
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.

.include "imag.inc"

.zeropage _PRG_BANK,_BANK_SHADOW, _CHR_BANK_NEXT

A53_REG_SELECT	= $5000
A53_REG_VALUE	= $8000

.section .nmi.150,"ax",@progbits
.globl swap_chr_bank_nmi
swap_chr_bank_nmi:
	lda #$00
	sta A53_REG_SELECT
	lda _CHR_BANK_NEXT
	sta A53_REG_VALUE

.section .nmi.300,"ax",@progbits
.globl restore_prg_bank_nmi
restore_prg_bank_nmi:
	lda #$01
	sta A53_REG_SELECT
	lda _PRG_BANK
	sta A53_REG_VALUE
	; Restore the A53_REG_SELECT value before returning from NMI
	; in case we interrupted a bank switch on the main thread
	lda _BANK_SHADOW
	sta A53_REG_SELECT

.section .text.set_chr_bank,"ax",@progbits
.weak set_chr_bank
set_chr_bank:
	sta _CHR_BANK_NEXT
	ldx #$00
	stx _BANK_SHADOW
	stx A53_REG_SELECT
	sta A53_REG_VALUE
	rts

.section .text.swap_chr_bank,"ax",@progbits
.weak swap_chr_bank
swap_chr_bank:
	sta _CHR_BANK_NEXT
	rts

.section .text.split_chr_bank,"ax",@progbits
.weak split_chr_bank
split_chr_bank:
	ldx #$00
	stx _BANK_SHADOW
	stx A53_REG_SELECT
	sta A53_REG_VALUE
	rts

.section .text.set_mirroring,"ax",@progbits

.weak set_mirroring
set_mirroring:
	and #0b11
	ora #__supervisor_outer_bank
	sta __rc2
	lda #$80
	sta _BANK_SHADOW
	sta A53_REG_SELECT
	lda __rc2
	sta A53_REG_VALUE
	rts

.section .text.get_prg_bank,"ax",@progbits
.globl __get_prg_bank
.weak get_prg_bank
__get_prg_bank:
get_prg_bank:
	lda _PRG_BANK
	rts

.section .text.set_prg_bank,"ax",@progbits
.globl __set_prg_bank
.weak set_prg_bank
__set_prg_bank:
set_prg_bank:
	sta _PRG_BANK
	lda #$01
	sta _BANK_SHADOW
	sta A53_REG_SELECT
	lda _PRG_BANK
	sta A53_REG_VALUE
	rts


.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
	tay
	lda _PRG_BANK
	pha
		tya
		jsr __set_prg_bank
		lda __rc2
		sta __rc18
		lda __rc3
		sta __rc19
		jsr __call_indir
	pla
	jmp __set_prg_bank
