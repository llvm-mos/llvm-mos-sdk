.include "imag.inc"

.global __do_init_stack

; Initialize soft stack pointer to MEMTOP
.section .init.100,"axR",@progbits
__do_init_stack:
  lda $2e5
  sta __rc0
  lda $2e6
  sta __rc1
