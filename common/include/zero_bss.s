; Zero out the BSS section before main.
.macro __zero_bss
    LDA #__bss_begin
    STA mos8(__rc2)
    LDA #__bss_begin+1
    STA mos8(__rc3)
    LDA #0
    LDX #<__bss_size
    LDY #>__bss_size
    JSR __memset
.endm
