; Immediately exit the program by returning from _start.

; Provides an implementation of C's _exit and _Exit; finalization (_fini) is not
; run.
.global _exit
.global _Exit

; On init, save the hardware stack pointer. Since _start is just _init, this
; will be its value at entry.
.section .init.100,"axR",@progbits
  tsx
  stx __save_s

.text
_exit:
_Exit:
  ; Restore the hard stack pointer to its value on entry.
  tay
  txa
  ldx __save_s
  txs
  tax
  tya

  ; Effectively return from _start. Since the value of A is preserved, it is
  ; forwarded back to the OS.
  rts

.section .noinit,"aw",@nobits
__save_s:
  .fill 1
