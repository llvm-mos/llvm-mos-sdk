; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 16.11.2002
;
; File descriptor management for the POSIX I/O routines
;


        .include        "cbm.inc"
        .include        "filedes.inc"

.text

;--------------------------------------------------------------------------
; freefd: Find a free file handle and return it in X. Return carry clear if we
; found one, return a carry if no free lfns are left.

freefd:

        ldx     #0
        clc
loop:   lda     fdtab,x
        beq     found
        inx
        cpx     #MAX_FDS
        bcc     loop
found:  rts

;--------------------------------------------------------------------------
; Data

.data

fdtab:  .byte   LFN_READ
        .byte   LFN_WRITE
        .byte   LFN_WRITE
        .fill   MAX_FDS-3

unittab:.byte   CBMDEV_KBD
        .byte   CBMDEV_SCREEN
        .byte   CBMDEV_SCREEN
        .fill   MAX_FDS-3
.global         fdtab   ; Handle table
.global         unittab ; Unit table
.global         freefd  ; Return a table entry

