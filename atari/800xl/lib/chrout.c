__attribute__((noinline)) void __chrout(char c) {
  if(__builtin_expect(c == '\n', 0)) c = 0x9b;
  __attribute__((leaf)) asm volatile(
    "tax\n"
    "lda $e407\n"
    "pha\n"
    "lda $e406\n"
    "pha\n"
    "txa\n"
    "rts\n"
    : "+a"(c) : : "p", "x", "y");
}
