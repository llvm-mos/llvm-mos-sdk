; Copyright (c) 2023 Rhys Weatherley
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "imag.inc"

; Initialize the system from the reset vector.
.global __do_reset
.section .init.50,"ax",@progbits
__do_reset:
; Fix the D and I flags.
  cld
  cli
; Set up the initial 6502 stack pointer.
  ldx #$ff
  txs

.text
; IRQBRK handler.
.global _irqbrk
.section .text._irqbrk,"axR",@progbits
_irqbrk:
  pha                   ; __systick_isr and __serial_isr use A and X.
  phx
  cld                   ; Just in case.
  jsr __systick_isr     ; Handle the system millisecond tick timer interrupt.
  jsr __serial_isr      ; Handle serial receive interrupts.
  plx
  pla
  jmp irq               ; Jump to the user-supplied IRQ handler.

; Default IRQ and NMI handler if the user's program hasn't defined one.
.global _irq_default
.section .text._irq_default,"axR",@progbits
_irq_default:
  rti
