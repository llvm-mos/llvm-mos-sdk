void __chrout(char c) {
  __attribute__((leaf)) asm volatile("jsr\t$ffd2" : "+a"(c) : : "p");
}
