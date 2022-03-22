.global __do_zero_bss

.section .init.20,"axR",@progbits
__do_zero_bss:
  jsr __zero_bss
