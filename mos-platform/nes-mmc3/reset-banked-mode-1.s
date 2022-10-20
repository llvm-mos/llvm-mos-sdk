.section .reset,"ax",@progbits
.globl _reset
_reset:
  lda #$40
  sta $8000
  sta $8001
  jmp _start

