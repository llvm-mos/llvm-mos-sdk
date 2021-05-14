.section .start,"ax",@progbits
.global _start
_start:
    ; Initialize soft stack pointer.
    LDA #mos16lo(__stack)
    STA mos8(__rc0)
    LDA #mos16hi(__stack)
    STA mos8(__rc1)

    ; Note: BSS is already zeroed.
    JSR main

    ; Write a nonzero value to FFF8 to quit.
    LDA #1
    STA $FFF8
