void __chrout(char c) {
  if (c == '\n')
    c = '\r';
  __attribute__((leaf)) asm volatile("jsr\t$ffd2" : "+a"(c) : : "p");
}
