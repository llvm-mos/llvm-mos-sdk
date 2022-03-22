.section .call_main,"axR",@progbits
  jsr main

.section .fini_rts,"axR",@progbits
  rts

; Make sure to search libraries for the after-main code to include.
.global __after_main
