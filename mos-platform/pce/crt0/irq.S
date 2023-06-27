; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https:;github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

; Default IRQ handlers.

.text

;; NMI is not used on PC Engine; no point in exposing it.
.weak nmi
nmi:
	rti

;; The following IRQs are exposed with a default 

;; Timer IRQ (IRQ0).
.section .irq_timer_begin,"axG",@progbits,irq_timer
.weak irq_timer
.global __default_irq_timer
irq_timer:
__default_irq_timer:
	phy
	phx
	pha

.section .irq_timer_end,"axG",@progbits,irq_timer
;; Acknowledge interrupt.
	lda $1403

	pla
	plx
	ply
	rti

;; VDC IRQ (IRQ1).
.section .irq_vdc_begin,"axG",@progbits,irq_vdc
.weak irq_vdc
.global __default_irq_vdc
irq_vdc:
__default_irq_vdc:
	phy
	phx
	pha

.section .irq_vdc_end,"axG",@progbits,irq_vdc
;; Acknowledge interrupt.
	lda mos16($0000)

	pla
	plx
	ply
	rti

;; External hardware IRQ (IRQ2).
.section .irq_ext_begin,"axG",@progbits,irq_ext
.weak irq_ext
.global __default_irq_ext
irq_ext:
__default_irq_ext:
	phy
	phx
	pha

.section .irq_ext_end,"axG",@progbits,irq_ext
	pla
	plx
	ply
	rti
