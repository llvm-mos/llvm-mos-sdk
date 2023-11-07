; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "atari2600.inc"

.align $10
.global _set_horiz_pos
_set_horiz_pos:
    sec                 ; set carry flag
    sta WSYNC           ; start a new line
div15:
    sbc #15             ; subtract 15
    bcs div15           ; branch until negative
    eor #7              ; calculate fine offset
    asl
    asl
    asl
    asl
    sta HMP0,x          ; set fine offset
    sta RESP0,x         ; fix coarse position
    rts
