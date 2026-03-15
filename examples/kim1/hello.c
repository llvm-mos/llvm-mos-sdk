// KIM-1 Hello World (unexpanded, 3.5K RAM)
// Uses putchar directly — printf is too large for the unexpanded KIM-1.

#include <stdio.h>

static void puts_kim1(const char *s) {
  while (*s)
    putchar(*s++);
  putchar('\n');
}

int main(void) {
  puts_kim1("HELLO FROM KIM-1!");
  puts_kim1("LLVM-MOS");
  return 0;
}
