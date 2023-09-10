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

.section .text._bank,"ax",@progbits
.global _BANK
_BANK: .byte $FF

.zeropage _PRG_BANK

.section .text.set_prg_bank,"ax",@progbits
.globl __set_prg_bank
.weak set_prg_bank
__set_prg_bank:
set_prg_bank:
	sta _PRG_BANK
	sta _BANK
	rts

.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
	tay
	lda _PRG_BANK
	pha
		sty _PRG_BANK
		sty _BANK
		lda __rc2
		sta __rc18
		lda __rc3
		sta __rc19
		jsr __call_indir
	pla
	jmp __set_prg_bank
