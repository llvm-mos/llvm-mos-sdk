#include <start.S>

; Initialize soft stack pointer to MEMTOP
.section .init.10,"axR",@progbits
  lda $2e5
  sta mos8(__rc0)
  lda $2e6
  sta mos8(__rc1)

.global __do_zero_bss

.section .init_last,"axR",@progbits
  jsr main
  jmp __exit_return ; Return to OS
