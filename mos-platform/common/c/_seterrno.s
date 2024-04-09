; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 2004-05-13
;
; __seterrno: Will set _errno to the value in A and return zero in A. Other
;             registers aren't changed. The function is C callable, but
;             currently only called from asm code.
;

.text

.globl   __seterrno
__seterrno:

        sta     _errno
        lda     #0
        sta     _errno+1
        rts
