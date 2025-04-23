; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Christian Groessler, Jan-2003
;
; int open(const char *name,int flags,...);
;

        .include "atari.inc"
        .include "fcntl.inc"
        .include "errno.inc"
        .include "fd.inc"
        .include "imag.inc"

        .globl open

open:
        pha                     ; push mode (only low byte matters)

        jsr     findfreeiocb
        beq     iocbok          ; we found one

        pla
        lda     #<EMFILE        ; "too many open files"
seterr: jsr     __directerrno
        lda     #$FF
        tax
        rts

        ; process the mode argument

iocbok: stx     __rc13
        jsr     clriocb         ; init with zero
        pla                     ; pop mode
        ldx     __rc13
        pha
        and     #O_APPEND
        beq     no_app
        pla
        and     #15
        cmp     #O_RDONLY       ; DOS supports append with write-only only
        beq     invret
        cmp     #O_RDWR
        beq     invret
        lda     #OPNOT|APPEND
        bne     set

invret: lda     #<EINVAL        ; file name is too long
        jmp     seterr

no_app: pla
        and     #15
        cmp     #O_RDONLY
        bne     l1
        lda     #OPNIN
set:    sta     ICAX1,x
        bne     cont

l1:     cmp     #O_WRONLY
        bne     l2
        lda     #OPNOT
        bne     set

l2:     ; O_RDWR
        lda     #OPNOT|OPNIN
        bne     set

        ; process the filename argument

cont:   lda     __rc2
        ldx     __rc3

        ldy     __rc13

        ;AX - points to filename
        ;Y  - iocb to use, if open needed
        jsr     newfd           ; maybe we don't need to open and can reuse an iocb
                                ; returns fd num to use in tmp2, all regs unchanged
        bcs     doopen          ; C set: open needed
        lda     #0              ; clears N flag
        beq     finish

doopen: sta     ICBAL,y
        txa
        sta     ICBAH,y
        ldx     __rc13
        lda     #OPEN
        sta     ICCOM,x
        jsr     CIOV

finish: bpl     ok
        sty     __rc12          ; remember error code
        lda     #CLOSE
        sta     ICCOM,x
        jsr     CIOV            ; close IOCB again since open failed
        jsr     fddecusage      ; and decrement usage counter of fd
        lda     __rc12          ; put error code into A
        jmp     __mappederrno

ok:     lda     __rc11          ; get fd
        ldx     #0
        stx     __oserror
        rts


; closeallfiles: Close all files opened by the program.

; This must happen after fclosing all stdio files.

.section .fini.200,"ax",@progbits
closeallfiles:

        lda     #MAX_FD_INDEX-1
loop:   ldx     #0
        pha
        jsr     close
        pla
        clc
        sbc     #0
        bpl     loop
