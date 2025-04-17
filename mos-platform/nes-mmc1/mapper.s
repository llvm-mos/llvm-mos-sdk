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

.zeropage _PRG_BANK, _CHR_BANK0, _CHR_BANK1, _MMC1_CTRL_NMI, _CHR_BANK0_CUR
.zeropage _CHR_BANK1_CUR, _MMC1_CTRL_CUR, _IN_PROGRESS

MMC1_CTRL	= $8000
MMC1_CHR0	= $a000
MMC1_CHR1	= $c000
MMC1_PRG	= $e000

; macro to write to an mmc1 register, which goes one bit at a time, 5 bits wide.
.macro mmc1_register_write addr
	.rept 4
		sta \addr
		lsr
	.endr
	sta \addr
.endmacro

.section .nmi.100,"ax",@progbits
	jsr bank_nmi

.section .text.bank_nmi,"ax",@progbits
.globl bank_nmi
bank_nmi:
	inc __reset_mmc1_byte
	lda _CHR_BANK0
	sta _CHR_BANK0_CUR
	mmc1_register_write MMC1_CHR0
	lda _CHR_BANK1
	sta _CHR_BANK1_CUR
	mmc1_register_write MMC1_CHR1
	lda _MMC1_CTRL_NMI
	sta _MMC1_CTRL_CUR
	mmc1_register_write MMC1_CTRL
	lda #0
	sta _IN_PROGRESS
	rts

.section .text.set_chr_bank_0,"ax",@progbits
.weak set_chr_bank_0
set_chr_bank_0:
	sta _CHR_BANK0
	rts

.section .text.set_chr_bank_1,"ax",@progbits
.weak set_chr_bank_1
set_chr_bank_1:
	sta _CHR_BANK1
	rts

.section .text.set_mirroring,"ax",@progbits
.weak set_mirroring
set_mirroring:
	and #0b11
	sta __rc2
	lda _MMC1_CTRL_NMI
	and #0b11100
	ora __rc2
	sta _MMC1_CTRL_NMI
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
	tay
.Lset:
	inc __reset_mmc1_byte
	ldx #1
	stx _IN_PROGRESS
	mmc1_register_write MMC1_PRG
	ldx _IN_PROGRESS
	beq .Lretry
	dex
	stx _IN_PROGRESS
	sty _PRG_BANK
	rts
.Lretry:
	tya
	jmp .Lset



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
	jsr __set_prg_bank
	rts
