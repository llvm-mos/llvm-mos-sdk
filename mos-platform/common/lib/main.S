.text
.global __main
.global _exit
.global _Exit

; For now the only task of this wrapper is to store hardware stack register.
; It allows us to 'longjmp' to __main caller in _exit function below

__main:
    TSX
    STX __save_s
    JMP __init_main

; Restore hardware stack register to value saved in __main and 'longjmp' to
; __main caller

_exit:
_Exit:
   STX mos8(__rc2)
   LDX __save_s
   TXS
   LDX mos8(__rc2)
   RTS

.section .noinit,"aw"
__save_s:
    .byte 00
