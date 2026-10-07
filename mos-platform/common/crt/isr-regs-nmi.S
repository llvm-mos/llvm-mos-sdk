; Private imaginary registers for suffixed ISRs using the "__nmi" suffix.
;
; This file defines the private zero-page registers used by functions compiled
; with interrupt_norecurse("__nmi"). Each even/odd register pair lives in its own section so --gc-sections can discard unused pairs; a
; small ISR pays only for the rc-pairs it actually touches.
;
; This is a normal archive member, so it is pulled in automatically only
; when a suffixed ISR references one of its symbols. No weak symbols or
; PROVIDE are needed: section-based definitions make the linker allocate the
; bytes in the existing zp MEMORY region (collected by zp-noinit-sections.ld's
; *(.zp .zp.*) wildcard).

.macro isr_reg_pair n, m
  .section .zp.isr_regs__nmi.\n, "zaw", @nobits
    .global __rc\n\()__nmi, __rc\m\()__nmi
    __rc\n\()__nmi: .fill 1
    __rc\m\()__nmi: .fill 1
.endm

isr_reg_pair 0, 1
isr_reg_pair 2, 3
isr_reg_pair 4, 5
isr_reg_pair 6, 7
isr_reg_pair 8, 9
isr_reg_pair 10, 11
isr_reg_pair 12, 13
isr_reg_pair 14, 15
isr_reg_pair 16, 17
isr_reg_pair 18, 19
isr_reg_pair 20, 21
isr_reg_pair 22, 23
isr_reg_pair 24, 25
isr_reg_pair 26, 27
isr_reg_pair 28, 29
isr_reg_pair 30, 31
