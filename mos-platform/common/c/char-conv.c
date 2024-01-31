__attribute__((always_inline, weak)) void __char_conv(char c, void (*emit)(char c)) {
  emit(c);
}
