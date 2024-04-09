; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 2002-11-16, 2009-02-22
;
; Scratch a file on disk
;

        .globl         scratch

;--------------------------------------------------------------------------
; scratch: Scratch a file on disk. Expects the name of the file to be already
; parsed. Returns an error code in A, which may either be the code read from
; the command channel, or another error when accessing the command channel
; failed.

scratch:

        ldx     fnunit
        jsr     opencmdchannel
        bne     done

        lda     #'S'            ; Scratch command
        sta     fncmd
        jsr     writefndiskcmd

        pha
        ldx     fnunit
        jsr     closecmdchannel
        pla

done:   rts
