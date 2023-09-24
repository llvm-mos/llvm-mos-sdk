#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_PRG_RAM_KB(32);

volatile char c[8100] = {1, [8099] = 2};

int main(void) {
  if (c[0] != 1 || c[8099] != 2)
    return EXIT_FAILURE;
  c[0] = 3;
  if (c[0] != 3)
    return EXIT_FAILURE;
  c[8099] = 4;
  if (c[8099] != 4)
    return EXIT_FAILURE;
  if (c[0] != 3)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
