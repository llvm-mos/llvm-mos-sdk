#include <stdio.h>

int main(void) {
  const char *cur = "HELLO, PUTCHAR!\n";
  while (*cur)
    putchar(*cur++);
  return 0;
}
