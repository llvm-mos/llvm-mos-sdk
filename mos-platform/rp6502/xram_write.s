; 2026, Rumbledethumps
;
; XRAM block copies, optimally unrolled.

.include "rp6502.inc"
.include "imag.inc"

.section .text.xram0_write,"ax",@progbits
.globl xram0_write
.type xram0_write,@function
xram0_write:
    sta RIA_ADDR0
    stx RIA_ADDR0+1
    lda #1
    sta RIA_STEP0
    ldx __rc5
    inx
    lda __rc4                   ; the whole eights of the partial page
    and #$F8
    tay
    beq .Lxram0_write_next
    clc                         ; start 256 - Y bytes back so Y wraps at the end
    adc __rc2
    sta __rc2
    bcs 1f
    dec __rc3
1:  tya
    eor #$FF
    tay
    iny
.Lxram0_write_page:
    .rept 8
    lda (__rc2),y
    sta RIA_RW0
    iny
    .endr
    bne .Lxram0_write_page
    inc __rc3
.Lxram0_write_next:
    dex
    bne .Lxram0_write_page
    lda __rc4
    and #7
    beq .Lxram0_write_done
    tax
.Lxram0_write_rest:
    lda (__rc2),y
    sta RIA_RW0
    iny
    dex
    bne .Lxram0_write_rest
.Lxram0_write_done:
    rts
.size xram0_write, .-xram0_write

.section .text.xram1_write,"ax",@progbits
.globl xram1_write
.type xram1_write,@function
xram1_write:
    sta RIA_ADDR1
    stx RIA_ADDR1+1
    lda #1
    sta RIA_STEP1
    ldx __rc5
    inx
    lda __rc4                   ; the whole eights of the partial page
    and #$F8
    tay
    beq .Lxram1_write_next
    clc                         ; start 256 - Y bytes back so Y wraps at the end
    adc __rc2
    sta __rc2
    bcs 1f
    dec __rc3
1:  tya
    eor #$FF
    tay
    iny
.Lxram1_write_page:
    .rept 8
    lda (__rc2),y
    sta RIA_RW1
    iny
    .endr
    bne .Lxram1_write_page
    inc __rc3
.Lxram1_write_next:
    dex
    bne .Lxram1_write_page
    lda __rc4
    and #7
    beq .Lxram1_write_done
    tax
.Lxram1_write_rest:
    lda (__rc2),y
    sta RIA_RW1
    iny
    dex
    bne .Lxram1_write_rest
.Lxram1_write_done:
    rts
.size xram1_write, .-xram1_write
