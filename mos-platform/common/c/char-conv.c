__attribute__((always_inline, weak)) void __from_ascii(char c,
                                                       void (*emit)(char c)) {
  emit(c);
}
