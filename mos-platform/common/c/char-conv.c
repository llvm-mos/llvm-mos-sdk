__attribute__((always_inline, weak)) void __from_ascii(char c,
                                                       void (*write)(char c)) {
  write(c);
}

__attribute__((always_inline, weak)) int __to_ascii(int (*read)(void)) {
  return read();
}
