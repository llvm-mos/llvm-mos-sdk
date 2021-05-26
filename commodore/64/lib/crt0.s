.include "init_stack.s"
.include "zero_bss.s"

.section .start,"ax",@progbits
.global _start
_start:
    __init_stack

    __zero_bss

    JSR main

    ; It's no longer safe to reenter BASIC.
    end: JMP end
