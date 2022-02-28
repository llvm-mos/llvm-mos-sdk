.global __do_init_stack

; Initialize soft stack pointer to MEMTOP
.section .init.10,"axR",@progbits
__do_init_stack:
  lda $2e5
  sta mos8(__rc0)
  lda $2e6
  sta mos8(__rc1)
