void __chrout(char c) {
  if(c == '\n') c = 0x9b;
  __attribute__((leaf)) asm volatile(
    "jsr\t$F2B0\n" : "+a"(c) : : "p", "x", "y");
}
