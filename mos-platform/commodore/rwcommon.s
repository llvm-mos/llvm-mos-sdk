; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 17.11.2002
;
; Common stuff for the read/write routines
;

        .globl         rwcommon

        .include        "errno.inc"
        .include        "filedes.inc"
        .include        "imag.inc"


;--------------------------------------------------------------------------
; rwcommon: Preprocess the parameters and place them into zero page locations.
; Return carry set if the handle is invalid, return carry clear if it is ok. If
; the carry is clear, the handle is returned in A.

rwcommon:

        cpx     #$01
        bcs     1f
        sta     __rc11

                                ; Note that buf is already in ptr1

        inc     __rc4
        inc     __rc5           ; Save count with each byte incremented separately

        ldy     #0
        sty     __rc6
        sty     __rc7           ; Clear ptr3

        lda     __rc11
        cmp     #MAX_FDS        ; Set carry if fd too large
1:      rts                     ; Return with result in carry
