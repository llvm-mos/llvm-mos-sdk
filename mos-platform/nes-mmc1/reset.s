.macro reset bank
  .section .reset_\bank,"ax",@progbits
    ; Reset the mapper so the last bank appears at $c000.
    inc $fffc
    ; Set up the mapper for the C runtime using the code in the last bank.
    jmp _start
  .short $fff4
  .short $fff4
  .short $fff4
.endm

.section .reset_last,"ax",@progbits
; Reset the mapper so the last bank appears at $c000.
inc $fffc
; Set up the mapper for the C runtime using the code in the last bank.
jmp _start
.short nmi
.short $fff4
.short irq

reset 0
reset 1
reset 2
reset 3
reset 4
reset 5
reset 6
reset 7
reset 8
reset 9
reset 10
reset 11
reset 12
reset 13
reset 14
