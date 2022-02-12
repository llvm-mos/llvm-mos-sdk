void __chrout(char c) {
  __attribute__((leaf)) asm volatile("jsr\tCHROUT" : "+a"(c) : : "p");
}
