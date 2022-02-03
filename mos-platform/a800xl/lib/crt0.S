#include <start.S>

.section .init_last,"axR",@progbits
  jsr main
  jmp __exit_return ; Return to OS
