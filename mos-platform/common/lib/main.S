.text
.global __main
.global __exit

__main:
    TSX
    STX __save_sp
    JMP main

__exit:
   STX __save_x
   LDX __save_sp
   TXS
   LDX __save_x
   rts

__save_sp:
    .byte 00
__save_x:
    .byte 00
