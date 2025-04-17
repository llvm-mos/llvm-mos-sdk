; ensure that ROM0 is selected on startup
; so that it matches the __current_bank variable
; which is zero-initialized

.section .init.055,"ax",@progbits
  sta $3F   ; A = 0 from init.050

