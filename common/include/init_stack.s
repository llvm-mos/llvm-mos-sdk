; Initialze soft stack pointer from __stack symbol.
.macro __init_stack
    LDA #mos16lo(__stack)
    STA mos8(__rc0)
    LDA #mos16hi(__stack)
    STA mos8(__rc1)
.endm
