#include <start.S>

; Initialize soft stack pointer.
#include <init_stack.S>

.section .init_last,"axR",@progbits
  jsr main
  jmp exit
