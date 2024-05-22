; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Christian Groessler, May-2000
;
; int __fastcall__ close(int fd);
;

        .include "atari.inc"
        .include "errno.inc"

        .globl  close

close:
        jsr     fdtoiocb_down           ; get iocb index into X and decr. usage count
        bmi     inverr
        bne     ok                      ; not last one -> don't close yet
        lda     #CLOSE
        sta     ICCOM,x
        jsr     CIOV
        bmi     closerr
ok:     ldx     #0
        stx     __oserror               ; clear system specific error code
        txa
        rts

inverr: lda     #<EINVAL
        jmp     __directerrno

closerr:
        tya
        jmp     __mappederrno

