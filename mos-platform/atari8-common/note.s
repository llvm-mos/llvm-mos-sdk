; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; char __note (int fd, fpos_t *pos);

        .include "atari.inc"
        .include "imag.inc"

        .globl  __note

__note:
        jsr     fdtoiocb
        bmi     error
        tax
        lda     #NOTE
        sta     ICCOM,x
        jsr     CIOV
        bmi     error
        ldy     #0
        lda     ICAX5,x
        sta     (__rc2),y
        iny
        lda     ICAX3,x
        sta     (__rc2),y
        iny
        lda     ICAX4,x
        sta     (__rc2),y
        iny
        lda     #0
        sta     (__rc2),y
        rts

error:
        ldy     #3
        lda     #$ff
store_error:
        sta     (__rc2),y
        dey
        bpl     store_error
        rts
