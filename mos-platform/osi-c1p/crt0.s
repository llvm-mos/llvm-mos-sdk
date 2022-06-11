; Assembler crt0 file to clear the screen before the
; call to main and to initialize the keyboard reading
; code.

.section .init.40,"axR",@progbits
  jsr __initkbhit
  jsr __clrscr

