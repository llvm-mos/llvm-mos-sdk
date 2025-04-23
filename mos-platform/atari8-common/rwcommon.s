; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; common iocb setup routine for read, write
; expects __fastcall__ parameters (int fd, void *buf, int count)
;
        .include "atari.inc"
        .include "errno.inc"
        .include "imag.inc"

        .globl __rwsetup


__rwsetup:
        jsr     fdtoiocb        ; convert handle to iocb
        bmi     iocberr         ; negative (X=$FF or A>$7F) on error.
        tax
        lda     __rc3           ; store address
        sta     ICBAH,x
        lda     __rc2
        sta     ICBAL,x
        lda     __rc5           ; store length
        sta     ICBLH,x
        lda     __rc4
        sta     ICBLL,x
        ora     ICBLH,x         ; returns Z if length is 0
        rts

iocberr:
        ldx     #$FF            ; indicate error + clear ZF
        rts

