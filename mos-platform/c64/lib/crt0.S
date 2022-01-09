#include <init_stack.S>

.section .start,"ax",@progbits
.global _start
_start:
    __init_stack

    JSR __zero_bss

    JSR __main

    ; It's no longer safe to reenter BASIC.
    end: JMP end
