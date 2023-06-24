; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

; Block moves on HuC6280 require a bit of hacking to be most efficient.
; The HuC6280 provides optimized (17+(6 cycles per byte)!) memory transfer
; instructions, but they only take immediate arguments. Therefore, build
; a subroutine in the imaginary register area and jump to it.

.include "imag.inc"

.global pce_memop

    .section .text.pce_memop, "ax", @progbits
; __rc2-__rc3 dest
; __rc4-__rc5 source
; __rc6       mode
;   X  -  A   length
pce_memop:
    sta __rc8
    stx __rc9
    lda __rc6
    ldx __rc2
    stx __rc6
    ldx __rc3
    stx __rc7
__pce_memop_inner:
    ldy __rc3
    sta __rc3
    lda #$60 ; RTS
    sta __rc10
    jsr __rc3
    sty __rc3
    rts