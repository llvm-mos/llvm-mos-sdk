.section .start,"ax",@progbits
.global _start
_start:
    ; Initialize soft stack pointer.
    LDA #mos16lo(__stack)
    STA mos8(__rc0)
    LDA #mos16hi(__stack)
    STA mos8(__rc1)

    ; FIXME: Zero BSS.
    JSR main

    ; It's no longer safe to reenter BASIC.
    end: JMP end
