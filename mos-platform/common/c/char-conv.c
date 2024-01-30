__attribute__((always_inline)) void __char_conv(char c, void (*emit)(char c)) {
  emit(c);
}
