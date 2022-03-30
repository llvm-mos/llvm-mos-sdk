; Fixed constants used by the compiler in ways that preclude immediate
; addressing.

.section .rodata,"a",@progbits

; Location that when used with BIT will set V. Compensates for the lack of a SEV
; instruction.
.global __set_v
__set_v:
  .byte 0xFF
