; Compiler temporary locations. These essentially behave as caller-saved
; registers; in particular, interrupt handlers must preserve them.

.section .noinit,"aw"

; Location to temporarily save the value of the A register.
.global __save_a
__save_a:
    .space 1

; Location to temporarily save the value of the Y register.
.global __save_y
__save_y:
    .space 1
