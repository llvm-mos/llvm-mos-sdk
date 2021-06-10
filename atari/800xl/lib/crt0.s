.section .start,"ax",@progbits
.global _start
_start:
    ; Initialize soft stack pointer to MEMTOP
    LDA $2e5
    STA mos8(__rc0)
    LDA $2e6
    STA mos8(__rc1)

    JSR __zero_bss

    JMP main
