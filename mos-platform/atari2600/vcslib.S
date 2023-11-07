
.include "atari2600.inc"

.align $10
.global set_horiz_pos
set_horiz_pos:
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
