; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

        .include "atari.inc"

; find a free iocb
; no entry parameters
; return ZF = 0/1 for not found/found
;        index in X if found
; all registers destroyed

.globl findfreeiocb
findfreeiocb:

        lda     #0
loop:   tax
        ldy     ICHID,x
        cpy     #$FF
        beq     found
        adc     #$10            ; C = 0
        bpl     loop            ; repeat for $10,$20,$30,...,$70
found:  rts
