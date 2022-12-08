.include "imag.inc"

.global __do_init_stack

; Initialze soft stack pointer from __stack symbol.
.section .init.100,"axR",@progbits
__do_init_stack:
  lda #mos16lo(__stack)
  sta __rc0
  lda #mos16hi(__stack)
  sta __rc1
