
.section .reset_stub,"ax",@progbits
_reset_stub:
; Set the $81 register for the PRG outer bank so that we bank $8000
    lda #$81
    sta $5000
    lda #$ff
    sta $8000
    jmp _start

.section .vectors,"ax",@progbits
.short nmi
.short _reset_stub
.short irq
