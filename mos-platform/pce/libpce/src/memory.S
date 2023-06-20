; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

; This is a hack of the highest order.
; The HuC6280 provides optimized (17+(6 cycles per byte)!) memory transfer
; instructions, but they only take immediate arguments. Therefore, build
; a subroutine in the imaginary register area and jump to it.

.include "imag.inc"

.global pce_memop
.global pce_rmemcpy
.global pce_memmove
.global pce_memset

    .section .text.pce_rmemcpy, "ax", @progbits
; __rc2-__rc3 dest
; __rc4-__rc5 source
;   X  -  A   length
pce_rmemcpy:
    sta __rc8
    stx __rc9
    sec
    sbc #1
    sta __rc6
    sax
    sbc #0
    sta __rc7
    sax
    clc
    adc __rc4
    sta __rc4
    sax
    adc __rc5
    sta __rc5
    lda __rc2
    clc
    adc __rc6
    sta __rc6
    lda __rc3
    adc __rc7
    sta __rc7
    lda #$C3 ; TDD
    bra __pce_memop_inner

    .section .text.pce_memmove, "ax", @progbits
; __rc2-__rc3 dest
; __rc4-__rc5 source
;   X  -  A   length
pce_memmove:
    ldy __rc4
    cpy __rc2
    bcc pce_rmemcpy
    ldy __rc5
    cpy __rc3
    bcc pce_rmemcpy
    bra pce_memcpy

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

    .section .text.pce_memset, "ax", @progbits
; __rc2-__rc3 dest
;   A         value
; __rc4 -  X  length
pce_memset:
    tay
    ; decrement 1
    txa
    sta __rc8
    bne .Lfirst_dec
    ldx __rc4
    beq .Ldone
    dec __rc4
.Lfirst_dec:
    dec __rc8
    ; write first value
    cla
    say
    sta (__rc2), y
    ; check if zero
    lda __rc4
    sta __rc9
    ora __rc8
    beq .Ldone
    ; write dest => source
    lda __rc2
    ldx __rc3
    sta __rc4
    stx __rc5
    ; write dest + 1 => dest
    clc
    adc #1
    sta __rc6
    sax
    adc #0
    sta __rc7
    ; call
    lda #$73
    bra __pce_memop_inner
.Ldone:
    rts