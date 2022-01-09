#include <stdio.h>

int main(void) {
  const char *cur = "HELLO, PUTCHAR!\n";
  while (*cur)
    __putchar(*cur++);
  return 0;
}
