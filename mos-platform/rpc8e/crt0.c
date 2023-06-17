asm(
  ".section .init.50,\"axR\",@progbits\n"
// Clear emulation mode.
  "  clc\n"
  "  xce\n"
// Initialize stack pointer to 0x01FF.
// RedPower 2 has a bug where the stack pointer is set to 0x0200 on boot, so
// an 8-bit-only TXS would have set it to 0x02FF, not 0x01FF.
  "  rep #$30\n"
  "  ldx #$01FF\n"
  "  txs\n"
// Work in 8-bit native mode.
  "  sep #$30\n"
// Clear decimal mode.
  "  cld\n"
// Enable RedBus by default.
  "  lda #$01\n"
  "  mmu #$02\n"
);
