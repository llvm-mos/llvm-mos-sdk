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

.zeropage _PRG_BANK, _CHR_BANK0, _CHR_BANK1, _MMC1_CTRL, _CHR_BANK0_NEXT
.zeropage _CHR_BANK1_NEXT, _MMC1_CTRL_NEXT, _IN_PROGRESS

MMC1_CTRL       = $8000
MMC1_CHR0       = $a000
MMC1_CHR1       = $c000
MMC1_PRG        = $e000

; macro to write to an mmc1 register, which goes one bit at a time, 5 bits wide.
.macro mmc1_register_write addr
        .rept 4
                sta \addr
                lsr
        .endr
        sta \addr
.endmacro

.section .nmi.100,"axR",@progbits
        jsr bank_nmi

.section .text.bank_nmi,"axR",@progbits
.globl bank_nmi
bank_nmi:
        inc __reset_mmc1_byte
; Flush out the shadow registers, incorporating any NEXT changes. In addition
; to applying any NEXT settings, this also finishes any writes in progress to
; ensure that the shadow state and the register state match for the NMI. The
; state setters contain logic to clean themselves up after detecting an
; NMI-interrupted write.
        lda _PRG_BANK
        mmc1_register_write MMC1_PRG
        lda _CHR_BANK0
        and #__chr_high_mask
        ora _CHR_BANK0_NEXT
        sta _CHR_BANK0
        mmc1_register_write MMC1_CHR0
        lda _CHR_BANK1
        and #__chr_high_mask
        ora _CHR_BANK1_NEXT
        sta _CHR_BANK1
        mmc1_register_write MMC1_CHR1
        lda _MMC1_CTRL
        and #0b01100
        ora _MMC1_CTRL_NEXT
        sta _MMC1_CTRL
        mmc1_register_write MMC1_CTRL
        lda #0
        sta _IN_PROGRESS
        rts


.section .text.banked_call,"ax",@progbits
.globl banked_call
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
