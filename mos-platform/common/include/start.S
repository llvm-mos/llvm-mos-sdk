; Implement _start using the _init and _fini system for dynamically building
; initializers and finalizers.

.text
.global _start

; _start is equivalent to _init; both are the start of the init sections.
.section .init_first,"axR",@progbits
_start:

; Targets must provide .init_last to call main and decide what should happen
; afterwards. A target could "jmp exit" to use the normal exit machinery.
; Alternatively "jmp __exit_return" exits by rts from _start without bringing in
; non-local jump mechanisms from _exit.

; _fini is taken to be a finalization function that can be called at any point.
.section .fini_last,"axR",@progbits
  rts
