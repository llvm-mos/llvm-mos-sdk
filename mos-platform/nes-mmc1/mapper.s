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
	ldx #<__prg_rom_is_512 
	beq .Lcontinue_bank_switch
	; save the new bank byte on the stack for safe keeping
	pha
	; check which bits changed
	eor _PRG_BANK
	; if the outer bank bit changed then we need to set a new outerbank
	and #%00010000
	beq .Lset_inner_bank
.Lset_new_outer_bank:
	; Flip the outer bank bit for _CHR_BANK0 and _CHR_BANK1
	lda _CHR_BANK0
	eor #%00010000
	jsr set_chr_bank_0_retry
	lda _CHR_BANK1
	eor #%00010000
	jsr set_chr_bank_1_retry
.Lset_inner_bank:
  	; restore the bank byte and put it in y so we can reload it on retry
  	pla
.Lcontinue_bank_switch:
	; bit 4 is PRG RAM en/disable, so use those from the current bank value
	ldx __rc2 ; preserve the current __rc2 value in X so we can use it as a temp
	and #%00001111
	sta __rc2 ; store the new bank bits
	lda _PRG_BANK ; load the current prg_ram enable bit
	and #%00010000
	ora __rc2 ; combine them together
	stx __rc2 ; restore the tmp register we used
  	tay
  	; original code below
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
	tay					; save current bank in y
	lda _PRG_BANK 		; load new bank in A
	pha					; push new bank to stack
    
    lda __rc2 			; push function pointer to stack
    pha
    lda __rc3
    pha
    
	tya					; restore current bank from A

    jsr __set_prg_bank 	; set the new bank
    
    pla				 	; restore function pointer from stack
    sta __rc19
    pla 
    sta __rc18
		
	jsr __call_indir
	pla
	jsr __set_prg_bank
	rts