; Immediately exit the program by jumping to the OS65V PROM monitor

RESET = 0xFF00        ; Reset address

; Provides an implementation of C's _exit and _Exit
.global _exit
.global _Exit

.text
_exit:
_Exit:
  ; Jump to the machine monitor entry point
  jmp RESET
