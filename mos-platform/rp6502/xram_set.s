; 2026, Rumbledethumps
;
; XRAM fill, optimally unrolled.

.include "rp6502.inc"
.include "imag.inc"

.section .text.xram0_set,"ax",@progbits
.globl xram0_set
.type xram0_set,@function
xram0_set:
    sta RIA_ADDR0
    stx RIA_ADDR0+1
    lda #1
    sta RIA_STEP0
    lda __rc3
    and #15
    beq .Lxram0_set_blocks
    tax
    lda __rc2
.Lxram0_set_rest:
    sta RIA_RW0
    dex
    bne .Lxram0_set_rest
.Lxram0_set_blocks:             ; the partial page, then whole pages
    ldx __rc4
    inx
    lda __rc3
    lsr
    lsr
    lsr
    lsr
    tay
    lda __rc2
    cpy #0
    beq .Lxram0_set_next
.Lxram0_set_pg:
    .rept 16
    sta RIA_RW0
    .endr
    dey
    bne .Lxram0_set_pg
.Lxram0_set_next:
    ldy #16
    dex
    bne .Lxram0_set_pg
    rts
.size xram0_set, .-xram0_set

.section .text.xram1_set,"ax",@progbits
.globl xram1_set
.type xram1_set,@function
xram1_set:
    sta RIA_ADDR1
    stx RIA_ADDR1+1
    lda #1
    sta RIA_STEP1
    lda __rc3
    and #15
    beq .Lxram1_set_blocks
    tax
    lda __rc2
.Lxram1_set_rest:
    sta RIA_RW1
    dex
    bne .Lxram1_set_rest
.Lxram1_set_blocks:             ; the partial page, then whole pages
    ldx __rc4
    inx
    lda __rc3
    lsr
    lsr
    lsr
    lsr
    tay
    lda __rc2
    cpy #0
    beq .Lxram1_set_next
.Lxram1_set_pg:
    .rept 16
    sta RIA_RW1
    .endr
    dey
    bne .Lxram1_set_pg
.Lxram1_set_next:
    ldy #16
    dex
    bne .Lxram1_set_pg
    rts
.size xram1_set, .-xram1_set
