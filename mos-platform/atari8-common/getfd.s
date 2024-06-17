; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Christian Groessler, Oct-2000
;
; allocates a new fd in the indirection table
;

        .include "atari.inc"
        .include "fd.inc"
        .include "imag.inc"

        .globl fdt_to_fdi,getfd

; fdt_to_fdi
; returns a fd_index entry pointing to the given ft_table entry
; get fd_table entry in A
; return C = 0/1 for OK/error
; return fd_index entry in A if OK
; registers destroyed
fdt_to_fdi:

        tay
        lda     #$ff
        tax
loop:   inx
        cmp     fd_index,x
        beq     found
        cpx     #MAX_FD_INDEX-1
        bcc     loop
        rts

found:  tya
        sta     fd_index,x
        txa
        clc
        rts

; getfd
; get a new fd pointing to a ft_table entry
; usage counter of ft_table entry incremented
; A - fd_table entry
; return C = 0/1 for OK/error
; returns fd in A if OK
; registers destroyed
getfd:

        jsr     fdt_to_fdi
        bcs     error

        pha
        tya
        asl     a
        asl     a                       ; also clears C
        tax
        inc     fd_table+ft_usa,x       ; increment usage counter
        pla
error:  rts

