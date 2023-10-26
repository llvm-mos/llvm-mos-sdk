.section .bss,"aw",@nobits
__mmusave:
  .fill 1

; MMU initialization needs to complete before any CRT initialization
.section .init.010,"axR",@progbits
        lda $FF00
        sta __mmusave
        lda #%00001110 ; map $4000-$BFFF to RAM, $C000-$FFFF to KERNAL/chargen
        sta $FF00

; restore MMU state after all other exit handlers have completed
.section .fini.990,"axR", @progbits
        lda __mmusave
        sta $FF00
