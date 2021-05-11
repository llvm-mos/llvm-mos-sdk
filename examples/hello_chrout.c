#include <chrout.h>

int main(void) {
  const char *cur = "HELLO, CHROUT!\n";
  while (*cur)
    __chrout(*cur++);
  return 0;
}
