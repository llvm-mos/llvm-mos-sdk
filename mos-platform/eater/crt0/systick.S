; Copyright (c) 2023 Rhys Weatherley
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "imag.inc"

#define VIA_T2CL    0x6008
#define VIA_T2CH    0x6009
#define VIA_ACR     0x600b
#define VIA_IFR     0x600d
#define VIA_IER     0x600e

#define T2COUNT     1000

; Initialize the system millisecond tick timer.
.global __do_init_systick
.section .init.250,"ax",@progbits
__do_init_systick:
  lda #$a0                      ; Enable T2 interrupts.
  sta VIA_IER
  lda #$00                      ; T2 in one-shot mode.
  sta VIA_ACR
  lda #mos16lo(T2COUNT)         ; T2 interrupt every 1000 clock ticks.
  sta VIA_T2CL
  lda #mos16hi(T2COUNT)
  sta VIA_T2CH

; Handle interrupts for the system millisecond tick timer.
.text
.global __systick_isr
.section .text.__systick_isr,"axR",@progbits
__systick_isr:
  lda VIA_IFR                   ; Has the T2 timer expired?
  and #$20
  beq .L__systick_isr_end
  inc __systick_value           ; Increment the system tick counter.
  bne .L__systick_isr_restart
  inc __systick_value+1
  bne .L__systick_isr_restart
  inc __systick_value+2
  bne .L__systick_isr_restart
  inc __systick_value+3
.L__systick_isr_restart:
  ldx VIA_T2CH                  ; Restart the one-shot T2 timer.
  lda VIA_T2CL
  cpx VIA_T2CH                  ; Has the high byte changed?
  bne .L__systick_isr_restart   ; If yes, we need to read T2CL/T2CH again.
  clc
  adc #mos16lo(T2COUNT - 24)    ; Adjust the T2 deadline for the elapsed ticks.
  sta VIA_T2CL
  txa
  adc #mos16hi(T2COUNT - 24)
  sta VIA_T2CH
.L__systick_isr_end:
  rts

; Get the value of the system millisecond tick timer.
.global millis
.section .text.millis,"ax",@progbits
millis:
  sei
  lda __systick_value+2
  sta __rc2
  lda __systick_value+3
  sta __rc3
  lda __systick_value
  ldx __systick_value+1
  cli
  rts

.section .zp.bss,"zaw",@nobits
__systick_value:
  .fill 4
