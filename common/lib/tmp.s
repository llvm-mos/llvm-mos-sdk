; Allocate space for compiler temporaries. These temporaries essentially behave
; as caller-saved registers; in particular, interrupt handlers must preserve
; them.

.section .noinit
    ; Location to temporarily save the value of the A register.
    .global __save_a
    __save_a:
        .space 1

    ; Location to temporarily save the value of the X register.
    .global __save_x
    __save_x:
        .space 1

    ; Location to temporarily save the value of the Y register.
    .global __save_y
    __save_y:
        .space 1
