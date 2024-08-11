; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; char __point (int fd, const fpos_t *pos);

        .include "atari.inc"
        .include "imag.inc"

        .globl  __point

__point:
        jsr     fdtoiocb
        bmi     invalid
        tax
        ldy     #3
        lda     (__rc2),y
        bne     invalid
        lda     #POINT
        sta     ICCOM,x
        dey
        lda     (__rc2),y
        sta     ICAX4,x
        dey
        lda     (__rc2),y
        sta     ICAX3,x
        dey
        lda     (__rc2),y
        sta     ICAX5,x
        jsr     CIOV
        bmi     cioerr
        lda     #0
        rts

invalid:
        lda     #<EINVAL
        jmp     __directerrno

cioerr:
        tya
        jmp     __mappederrno
