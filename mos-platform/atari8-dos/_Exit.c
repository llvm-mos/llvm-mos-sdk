// Atari DOS 2.5 (etc?) does not correctly detect if a chunk after the first
// clobbers the DUP, so it may crash after a RTS to DOS. Even if a DUP clobber
// is detected, the effect is the same as a JMP through DOSVEC, so may as well.
_Noreturn void _Exit(int status) {
  // JMP (DOSVEC)
  asm volatile("jmp ($a)");
  __builtin_unreachable();
}
