.text

; The FDS BIOS has a built-in IRQ and NMI multiplexer.
; For NMIs, it includes one built-in handler (used by its
; vertical interrupt wait function) and support for
; three custom handlers.
; For IRQs, it includes three built-in handlers (used for
; disk reading and I/O) and support for one custom handler.
; The used NMI handler is chosen by the value at $0100,
; while the IRQ handler is chosen by the value at $0101.

; Called when $0101 is set to %11xxxxxx
.section .irq_begin,"axG",@progbits,irq
.weak irq
.global __default_irq
irq:
__default_irq:
	pha
	txa
	pha
	tya
	pha

.section .irq_end,"axG",@progbits,irq
;; ack irq
	lda $4030

	pla
	tay
	pla
	tax
	pla
	rti

; Called when $0100 is set to %01xxxxxx
.section .nmi_user_1_begin,"axG",@progbits,nmi_user_1
.weak nmi_user_1
.global __default_nmi_user_1
nmi_user_1:
__default_nmi_user_1:
		pha
		txa
		pha
		tya
		pha

.section .nmi_user_1_end,"axG",@progbits,nmi_user_1
		pla
		tay
		pla
		tax
		pla
		rti

; Called when $0100 is set to %10xxxxxx
.section .nmi_user_2_begin,"axG",@progbits,nmi_user_2
.weak nmi_user_2
.global __default_nmi_user_2
nmi_user_2:
__default_nmi_user_2:
	pha
	txa
	pha
	tya
	pha

.section .nmi_user_2_end,"axG",@progbits,nmi_user_2
	pla
	tay
	pla
	tax
	pla
	rti

; Called when $0100 is set to %11xxxxxx
.section .nmi_user_3_begin,"axG",@progbits,nmi_user_3
.weak nmi_user_3
.global __default_nmi_user_3
nmi_user_3:
__default_nmi_user_3:
	pha
	txa
	pha
	tya
	pha

.section .nmi_user_3_end,"axG",@progbits,nmi_user_3
	pla
	tay
	pla
	tax
	pla
	rti
