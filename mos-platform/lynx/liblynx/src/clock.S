; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

.include "lynx.inc"

.bss
clock_count:        .space    3

.text

;-----------------------------------------------------------------------------
; Enable the interrupt that clock needs.
;
.global lynx_clock_init
lynx_clock_init:
        lda     #%10000000
        tsb     VTIMCTLA
        rts

;-----------------------------------------------------------------------------
; Get the current clock ticks
; out: A/X/__rc2/__rc3 - tick value (24-bit, top byte always 0)
.global lynx_clock_getticks
lynx_clock_getticks:
        php
        sei                     ; Disable interrupts

        lda     clock_count     ; Read the clock counter
        ldx     clock_count+1
        ldy     clock_count+2
        sty     __rc2
        stz     __rc3

        plp                     ; Re-enable interrupts
        rts

;-----------------------------------------------------------------------------
; This interrupt handler increments a 24-bit counter at every video
; vertical-blanking time.
;
.section .irq.400,"ax",@progbits
.global __irq_clock
__irq_clock:
        lda     INTSET
        and     #VBL_INTERRUPT
        beq     0f              ; Not vertical-blank interrupt

        inc     clock_count
        bne     0f
        inc     clock_count+1
        bne     0f
        inc     clock_count+2
0:
