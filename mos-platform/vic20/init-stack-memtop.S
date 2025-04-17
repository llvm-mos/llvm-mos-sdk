.include "imag.inc"

.global __do_init_stack

; Initialze soft stack pointer from KERNAL MEMTOP.
.section .init.100,"ax",@progbits
__do_init_stack:
  sec
  jsr MEMTOP
  stx __rc0
  sty __rc1
