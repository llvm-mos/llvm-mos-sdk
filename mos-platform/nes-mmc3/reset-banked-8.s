.section .reset,"ax",@progbits
.globl _reset
_reset:
  lda #7
  sta $8000
  lda #__fixed_bank
  sta $8001
  jmp _start

