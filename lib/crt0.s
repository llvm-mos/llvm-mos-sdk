.section __start,"ax",@progbits
.global _start
_start:
    ; Eventually this will zero BSS, set up the soft stack, etc.
    JMP main