void __chrout(char c) {
  __attribute__((leaf)) asm volatile("jsr\t__CHROUT" : "+a"(c) : : "p");
}
