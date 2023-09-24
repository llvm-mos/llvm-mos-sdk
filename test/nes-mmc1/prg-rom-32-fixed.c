#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_PRG_ROM_KB(32);

volatile const char c[32000] = {1, [31999] = 2};

int main(void) {
  if (c[0] != 1)
    return EXIT_FAILURE;
  if (c[31999] != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
