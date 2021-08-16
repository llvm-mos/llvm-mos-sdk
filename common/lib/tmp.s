; Compiler temporary locations. These essentially behave as caller-saved
; registers; in particular, interrupt handlers must preserve them.

.section .noinit,"aw"

; Location to temporarily save the value of the A register.
.global __save_a
__save_a:
    .space 1

; Pointer containing target of indirect call.
.align 2 ; Prevent NMOS bug when the pointer is on a page boundary.
.global __call_indir_target
__call_indir_target:
    .space 2
