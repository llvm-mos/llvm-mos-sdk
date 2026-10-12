; Private soft stack for "__irq" suffixed ISRs.
;
; This archive member defines __stack__irq atop a small (~128 B) .noinit
; buffer. The prologue of an interrupt_norecurse("__irq") handler references
; __stack__irq and initializes the private soft stack pointer
; (__rc0__irq / __rc1__irq) from it, but only when some function in the
; handler's call tree needs a soft-stack frame (e.g. it recurses). Otherwise
; this member is not linked at all.
;
; User override: link an object defining __stack__irq before this archive
; member to use a custom stack location.

.section .noinit.isr_stack__irq, "aw", @nobits
.global __stack__irq
__isr_stack__irq_buf:
  .fill 128
__stack__irq:
