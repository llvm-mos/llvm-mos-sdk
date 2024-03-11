; Initialize the CPU.
.section .init.50,"axR",@progbits
; Fix the D flag.
  cld
; Set up the initial 6502 stack pointer.
  ldx #$ff
  txs
