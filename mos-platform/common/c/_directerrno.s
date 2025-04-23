; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; 2003-08-12, Ullrich von Bassewitz
; 2015-09-24, Greg King
;
; Helper function for several high-level file functions.
;

        .include        "errno.inc"

; ----------------------------------------------------------------------------
; int __fastcall__ __directerrno (unsigned char code);
; /* Set errno to a specific error code, clear __oserror, and return -1. Used
; ** by the library.
; */

.globl __directerrno
__directerrno:
        jsr     __seterrno             ; Set errno (returns with .A = 0)
        sta     __oserror              ; Clear __oserror
        lda     #$FF                    ; Return -1
        tax
        rts
