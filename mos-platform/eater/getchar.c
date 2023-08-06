#include <stdio.h>
#include <chrin.h>

int getchar(void) {
  int c = __chrin();
  if (c == '\r')
    c = '\n';
  return c;
}
