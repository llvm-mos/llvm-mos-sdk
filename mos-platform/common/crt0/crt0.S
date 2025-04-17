.section .call_main,"ax",@progbits
  jsr main

.section .fini_rts,"ax",@progbits
  rts

; Make sure to search libraries for the after-main code to include.
.global __after_main
