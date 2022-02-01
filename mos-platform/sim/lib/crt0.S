#include <start.S>

.section .init_last,"axR",@progbits
  jsr main
  jmp exit
