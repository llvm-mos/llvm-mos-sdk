.include "c128.inc"

.bss
__mmusave:
  .fill 1

; MMU initialization needs to complete before any CRT initialization
.section .init.010,"ax",@progbits
        lda MMU_CR
        sta __mmusave
        lda MMU_CFG_RAM0_KERNAL ; map $4000-$BFFF to RAM, $C000-$FFFF to KERNAL/chargen
        sta MMU_CR

; restore MMU state after all other exit handlers have completed
.section .fini.990,"ax", @progbits
        lda __mmusave
        sta MMU_CR
