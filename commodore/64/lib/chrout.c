void __chrout(char c) {
  if (__builtin_expect(c == '\n', 0)) c = '\r';
  __attribute__((leaf)) asm volatile("jsr\t$ffd2" : "+a"(c) : : "p");
}
