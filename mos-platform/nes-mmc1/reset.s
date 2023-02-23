.section .reset,"ax",@progbits
; Reset the mapper so the last bank appears at $c000.
inc $fffc
; Unused, since the bank has changed.
.skip 3
.short $fff4
.short $fff4
.short $fff4

.section .reset_fixed,"ax",@progbits
; Reset the mapper so the last bank appears at $c000.
inc $fffc
; Set up the mapper for the C runtime using the code in the last bank.
jmp _start
.short nmi
.short $fff4
.short irq
