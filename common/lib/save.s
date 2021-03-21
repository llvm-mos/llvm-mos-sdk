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

    .global _SaveP
    _SaveP:
        .space 1

    .global _SaveImagLo
    _SaveImagLo:
        .space 1

    .global _SaveImagHi
    _SaveImagHi:
        .space 1