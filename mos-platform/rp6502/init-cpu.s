; Initialize the CPU.
.section .init.50,"ax",@progbits
; Set up the initial 6502 stack pointer.
  ldx #$ff
  txs
