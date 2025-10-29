; SNES Interrupt Vector Handlers for LLVM-MOS (6502 compatible)
; Based on vectors.asm reference from wdc816cc

.section .text.vectors,"ax",@progbits

; External C function references
.extern irq_cop_emu
.extern irq_brk_emu  
.extern irq_abort_emu
.extern irq_nmi_emu
.extern irq_blank_emu
.extern _start

; COP (Co-Processor) interrupt handler
.global COP
COP:
    pha
    txa
    pha
    tya
    pha
    php
    ; Save zero page registers that LLVM-MOS might use
    lda $00
    pha
    lda $01
    pha
    lda $02
    pha
    lda $03
    pha
    lda $04
    pha
    lda $05
    pha
    lda $06
    pha
    lda $07
    pha
    jsr irq_cop_emu
    ; Restore zero page registers
    pla
    sta $07
    pla
    sta $06
    pla
    sta $05
    pla
    sta $04
    pla
    sta $03
    pla
    sta $02
    pla
    sta $01
    pla
    sta $00
    plp
    pla
    tay
    pla
    tax
    pla
    rti

; BRK (Break) interrupt handler  
.global BRK
BRK:
    pha
    txa
    pha
    tya
    pha
    php
    ; Save zero page registers that LLVM-MOS might use
    lda $00
    pha
    lda $01
    pha
    lda $02
    pha
    lda $03
    pha
    lda $04
    pha
    lda $05
    pha
    lda $06
    pha
    lda $07
    pha
    jsr irq_brk_emu
    ; Restore zero page registers
    pla
    sta $07
    pla
    sta $06
    pla
    sta $05
    pla
    sta $04
    pla
    sta $03
    pla
    sta $02
    pla
    sta $01
    pla
    sta $00
    plp
    pla
    tay
    pla
    tax
    pla
    rti

; ABORT interrupt handler
.global ABORT
ABORT:
    pha
    txa
    pha
    tya
    pha
    php
    ; Save zero page registers that LLVM-MOS might use
    lda $00
    pha
    lda $01
    pha
    lda $02
    pha
    lda $03
    pha
    lda $04
    pha
    lda $05
    pha
    lda $06
    pha
    lda $07
    pha
    jsr irq_abort_emu
    ; Restore zero page registers
    pla
    sta $07
    pla
    sta $06
    pla
    sta $05
    pla
    sta $04
    pla
    sta $03
    pla
    sta $02
    pla
    sta $01
    pla
    sta $00
    plp
    pla
    tay
    pla
    tax
    pla
    rti

; NMI (Non-Maskable Interrupt) handler
.global NMI
NMI:
    pha
    txa
    pha
    tya
    pha
    php
    ; Save zero page registers that LLVM-MOS might use
    lda $00
    pha
    lda $01
    pha
    lda $02
    pha
    lda $03
    pha
    lda $04
    pha
    lda $05
    pha
    lda $06
    pha
    lda $07
    pha
    ; Acknowledge NMI interrupt
    lda $4210       ; Read NMI status to acknowledge
    jsr irq_nmi_emu
    ; Restore zero page registers
    pla
    sta $07
    pla
    sta $06
    pla
    sta $05
    pla
    sta $04
    pla
    sta $03
    pla
    sta $02
    pla
    sta $01
    pla
    sta $00
    plp
    pla
    tay
    pla
    tax
    pla
    rti

; IRQ (Interrupt Request) handler
.global IRQ
IRQ:
    pha
    txa
    pha
    tya
    pha
    php
    ; Save zero page registers that LLVM-MOS might use
    lda $00
    pha
    lda $01
    pha
    lda $02
    pha
    lda $03
    pha
    lda $04
    pha
    lda $05
    pha
    lda $06
    pha
    lda $07
    pha
    ; Acknowledge IRQ interrupt
    lda $4211       ; Read IRQ status to acknowledge
    jsr irq_blank_emu
    ; Restore zero page registers
    pla
    sta $07
    pla
    sta $06
    pla
    sta $05
    pla
    sta $04
    pla
    sta $03
    pla
    sta $02
    pla
    sta $01
    pla
    sta $00
    plp
    pla
    tay
    pla
    tax
    pla
    rti

; Dummy IRQ handler (for reserved vectors)
.global DIRQ
DIRQ:
    rti
    
.weak irq_cop_emu
irq_cop_emu:
    rti

.weak irq_brk_emu
irq_brk_emu:
    rti

.weak irq_abort_emu
irq_abort_emu:
    rti

.weak irq_nmi_emu
irq_nmi_emu:
    rti

.weak irq_blank_emu
irq_blank_emu:
    rti
