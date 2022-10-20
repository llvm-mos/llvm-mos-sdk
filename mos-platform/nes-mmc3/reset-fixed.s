.section .reset,"ax",@progbits
.globl _reset
_reset:
  ldx #6
  ldy #0
  stx $8000
  sty $8001
  inx
  iny
  stx $8000
  sty $8000
  jmp _start

