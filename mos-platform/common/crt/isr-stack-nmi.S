; Private soft stack for "__nmi" suffixed ISRs.
;
; This archive member defines __stack__nmi atop a small (~128 B) .noinit
; buffer. The prologue of an interrupt_norecurse("__nmi") handler references
; __stack__nmi and initializes the private soft stack pointer
; (__rc0__nmi / __rc1__nmi) from it, but only when some function in the
; handler's call tree needs a soft-stack frame (e.g. it recurses). Otherwise
; this member is not linked at all.
;
; User override: link an object defining __stack__nmi before this archive
; member to use a custom stack location.

.section .noinit.isr_stack__nmi, "aw", @nobits
.global __stack__nmi
__isr_stack__nmi_buf:
  .fill 128
__stack__nmi:
