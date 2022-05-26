; Assembler crt0 file to clear the screen before the
; call to main.

.section .init.40,"axR",@progbits
  jsr __clrscr

