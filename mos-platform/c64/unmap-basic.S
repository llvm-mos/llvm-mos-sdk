; Switch out the BASIC ROM bank from $A000 to $BFFF.
; This opens up 50KB of contiguous RAM from $0801-$CFFF.
; KERNAL ROM at $E000-$FFFF and I/O at $D000-$DFFF are still mapped.



; bank switching needs to complete before any CRT initialization
.section .init.010,"axR",@progbits
        ldx #$2F ; restore default CPU I/O port data directions
        stx 0    ;
        ldx #$3E ; LORAM = 0
        stx 1    ; switch out BASIC ROM at $A000-$BFFF for RAM



; restore BASIC ROM after all other exit handlers have completed
.section .fini.990,"axR", @progbits
        ldx #$3F ; LORAM = 1
        stx 1    ; switch in BASIC ROM at $A000-$BFFF

