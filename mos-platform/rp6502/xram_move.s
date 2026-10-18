; 2026, Rumbledethumps
;
; XRAM to XRAM move, optimally unrolled.

.include "rp6502.inc"
.include "imag.inc"

.section .text.xram_move,"ax",@progbits
.globl xram_move
.type xram_move,@function
xram_move:
    sta RIA_ADDR1               ; dest
    stx RIA_ADDR1+1
    sta __rc6
    stx __rc7
    sec                         ; dest - src < count means backward
    sbc __rc2
    tay
    txa
    sbc __rc3
    tax
    tya
    cmp __rc4
    txa
    sbc __rc5
    bcc .Lxram_move_back
    lda __rc2
    sta RIA_ADDR0
    lda __rc3
    sta RIA_ADDR0+1
    lda #1
    bne .Lxram_move_step
.Lxram_move_back:               ; C is clear, so X:Y = count - 1
    lda __rc4
    sbc #0
    tay
    lda __rc5
    sbc #0
    tax
    tya                         ; the last byte of each region
    clc
    adc __rc2
    sta RIA_ADDR0
    txa
    adc __rc3
    sta RIA_ADDR0+1
    tya
    clc
    adc __rc6
    sta RIA_ADDR1
    txa
    adc __rc7
    sta RIA_ADDR1+1
    lda #$FF
.Lxram_move_step:
    sta RIA_STEP0
    sta RIA_STEP1
    lda __rc4
    and #7
    beq .Lxram_move_blocks
    tax
.Lxram_move_rest:
    lda RIA_RW0
    sta RIA_RW1
    dex
    bne .Lxram_move_rest
.Lxram_move_blocks:             ; the partial page, then whole pages
    ldx __rc5
    inx
    lda __rc4
    lsr
    lsr
    lsr
    tay
    beq .Lxram_move_next
.Lxram_move_pg:
    .rept 8
    lda RIA_RW0
    sta RIA_RW1
    .endr
    dey
    bne .Lxram_move_pg
.Lxram_move_next:
    ldy #32
    dex
    bne .Lxram_move_pg
    rts
.size xram_move, .-xram_move
