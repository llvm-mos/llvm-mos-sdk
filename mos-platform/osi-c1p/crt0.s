; Assembler crt0 file to clear the screen before the
; call to main and to initialize the keyboard reading
; code.

.section .init.400,"ax",@progbits
  jsr __clrscr

