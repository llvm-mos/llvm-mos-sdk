.text
.global __main
.global __exit

; For now the only task of this wrapper is to store hardware stack register.
; It allows us to 'longjmp' to __main caller in __exit function below

__main:
    TSX
    STX __save_s
    JMP main

; Restore hardware stack register to value saved in __main and 'longjmp' to
; main caller

__exit:
   STX mos8(__rc2)
   LDX __save_s
   TXS
   LDX mos8(__rc2)
   RTS

__save_s:
    .byte 00
