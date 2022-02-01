#include <start.S>

.global __do_zero_bss

.section .init_last,"axR",@progbits
  jsr main
  jmp __exit_return ; Return to OS
