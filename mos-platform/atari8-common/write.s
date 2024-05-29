; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; int __fastcall__ write (int fd, const void* buf, unsigned count);
;
        .include "atari.inc"
        .include "errno.inc"
        .globl write

write:
        jsr     __rwsetup       ; do common setup
        beq     write9          ; if size 0, it's a no-op
        cpx     #$FF            ; invalid iocb?
        beq     _inviocb
        lda     #PUTCHR
        sta     ICCOM,x
        jsr     CIOV
        bpl     write9
        tya
        jmp     __mappederrno   ; update errno

write9:
        lda     ICBLL,x         ; get buf len low
        pha
        lda     ICBLH,x         ; buf len high
        tax
        lda     #0
        sta     __oserror      ; clear system dependend error code
        pla
        rts

_inviocb:
        lda     #<EINVAL
        jmp     __directerrno

