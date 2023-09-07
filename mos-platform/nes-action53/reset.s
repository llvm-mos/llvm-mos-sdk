
.section .prg_rom_fixed.reset_stub,"ax",@progbits
.weak reset_stub
.globl __reset_stub
reset_stub:
__reset_stub:
; Set the $81 register for the PRG outer bank so that we bank $8000
    lda #$81
    sta $5000
    lda #$ff
    sta $8000
    lda #2
    jsr set_mirroring
    jmp _start

.section .vectors,"ax",@progbits
.short nmi
.short reset_stub
.short irq
