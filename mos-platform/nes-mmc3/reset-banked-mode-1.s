.zeropage __bank_select_hi

.section .reset,"ax",@progbits
.globl _reset
_reset:
  lda #$40
  sta $8000
  sta $8001
  jmp _start

.section .init.250,"ax",@progbits
  lda #$40
  sta __bank_select_hi
