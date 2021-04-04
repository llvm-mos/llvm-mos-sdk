; Allocate space for absolute memory used to temporarily save and restore
; register values.

.section .noinit
    .global _SaveA
    _SaveA:
        .space 1

    .global _SaveX
    _SaveX:
        .space 1

    .global _SaveY
    _SaveY:
        .space 1
