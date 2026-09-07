; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

.include "lynx.inc"
.include "extzp.inc"

; ------------------------------------------------------------------------
; Mikey and Suzy init data, reg offsets and data

.zeropage IntVal

.rodata

SuzyInitData:
        .byte $7f,$7f,$00,$00,$24,$f3,$01
SuzyInitReg:
        .byte $28,$2a,$04,$06,$92,$83,$90
SuzyInitRegEnd:
        .set SuzyRegSize, SuzyInitRegEnd-SuzyInitReg

MikeyInitData:
        .byte $9e,$18,$68,$1f,$00,$00,$00,$00,$00,$ff,$1a,$1b,$04,$0d,$29
MikeyInitReg:
        .byte $00,$01,$08,$09,$20,$28,$30,$38,$44,$50,$8a,$8b,$8c,$92,$93
MikeyInitRegEnd:
        .set MikeyRegSize, MikeyInitRegEnd-MikeyInitReg

; ------------------------------------------------------------------------
; Actual code

.section .init.010,"ax",@progbits

; Set up the system.

        sei
        ldx     #$FF
        txs

; Init the bank switching.

         lda     #$C
         sta     MAPCTL          ; $FFF9

; Disable all timer interrupts.

        lda     #$80
        trb     TIM0CTLA
        trb     TIM1CTLA
        trb     TIM2CTLA
        trb     TIM3CTLA
        trb     TIM5CTLA
        trb     TIM6CTLA
        trb     TIM7CTLA

; Disable the TX/RX IRQ; set to 8E1.

        lda     #PAREN|RESETERR|TXOPEN|PAREVEN  ; #%00011101
        sta     SERCTL

; Clear all pending interrupts.

        lda     INTSET
        sta     INTRST

; Init Mickey.

        ldx     #MikeyRegSize
mloop:  ldy     MikeyInitReg,x
        lda     MikeyInitData,x
        sta     $fd00,y
        dex
        bpl     mloop

; These are RAM-shadows of read-only regs.

        ldx     #$1b
        stx     __iodat
        dex                     ; $1A
        stx     __iodir
        ldx     #$d
        stx     __viddma

; Init Suzy.

        ldx     #SuzyRegSize
sloop:  ldy     SuzyInitReg,x
        lda     SuzyInitData,x
        sta     $fc00,y
        dex
        bpl     sloop

        lda     #$24
        sta     __sprsys

; Init default IRQ stub
        lda     #<__default_irq
        ldx     #>__default_irq
        sei
        sta     INTVECTL
        stx     INTVECTH

        cli

.section .irq_begin,"ax",@progbits
.global __default_irq
__default_irq:
        phy
        phx
        pha

; load the current bit flags and save for later
        lda     INTSET
        sta     IntVal

.section .irq_end,"ax",@progbits
; reset interrupt flags based on store value at start of irq
        lda     IntVal
        sta     INTRST

        pla
        plx
        ply
        rti
