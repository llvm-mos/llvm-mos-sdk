; Helpers for building RIA API shims

.include "rp6502.inc"
.include "imag.inc"

; void ria_push_long(unsigned long val);
.globl ria_push_long
ria_push_long:
    ldy __rc3
    sty RIA_XSTACK
    ldy __rc2
    sty RIA_XSTACK
; void ria_push_int(unsigned int val);
.globl ria_push_int
ria_push_int:
    stx RIA_XSTACK
    sta RIA_XSTACK
    rts

; long ria_pop_long(void);
.globl ria_pop_long
ria_pop_long:
    jsr ria_pop_int
    ldy RIA_XSTACK
    sty __rc2
    ldy RIA_XSTACK
    sty __rc3
    rts

; int ria_pop_int(void);
.globl ria_pop_int
ria_pop_int:
    lda RIA_XSTACK
    ldx RIA_XSTACK
    rts

; void ria_set_axsreg(unsigned long axsreg);
.globl ria_set_axsreg
ria_set_axsreg:
    ldy __rc2
    sty RIA_SREG
    ldy __rc3
    sty RIA_SREG+1
; void ria_set_ax(unsigned int ax);
.globl ria_set_ax
ria_set_ax:
    stx RIA_X
    sta RIA_A
    rts

; int ria_call_int(unsigned char op);
.globl ria_call_int
ria_call_int:
    sta RIA_OP
    jmp RIA_SPIN

; long ria_call_long(unsigned char op);
.globl ria_call_long
ria_call_long:
    sta RIA_OP
    jsr RIA_SPIN
    ldy RIA_SREG
    sty __rc2
    ldy RIA_SREG+1
    sty __rc3
    rts
