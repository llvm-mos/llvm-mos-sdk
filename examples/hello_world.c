#include <chrout.h>

int main(void) {
  const char *cur = "HELLO, WORLD!\n";
  while (*cur)
    __chrout(*cur++);
  return 0;
}
