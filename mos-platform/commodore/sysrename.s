; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 2009-02-22
;
; unsigned char __fastcall__ _sysrename (const char *oldpath, const char *newpath);
;

        .globl         __sysrename

        .include        "imag.inc"

;--------------------------------------------------------------------------
; __sysrename:

__sysrename:
        lda     __rc2
        pha
        lda     __rc4
        sta     __rc2
        lda     __rc3
        pha
        lda     __rc5
        sta     __rc3

        jsr     _translate_filename
        lda     __rc2
        ldx     __rc3

        jsr     fnparse         ; Parse first filename
        bne     done

        lda     #'='
        jsr     fnadd

        pla
        sta     __rc3
        pla
        sta     __rc2
        jsr     _translate_filename
        ldy     #0
        jsr     fnparsename     ; Parse second filename
        bne     done

        ldx     fnunit
        jsr     opencmdchannel
        bne     done

        lda     #'R'            ; Rename command
        sta     fncmd
        jsr     writefndiskcmd

;       ldx     fnunit
;       jsr     readdiskerror

        pha
        ldx     fnunit
        jsr     closecmdchannel
        pla

done:   rts
