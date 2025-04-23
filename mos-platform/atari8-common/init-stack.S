.include "imag.inc"

.global __do_init_stack

; Initialize soft stack pointer to MEMTOP+1
.section .init.100,"ax",@progbits
__do_init_stack:
  clc
  lda $2e5
  adc #1
  sta __rc0
  lda $2e6
  adc #0
  sta __rc1
