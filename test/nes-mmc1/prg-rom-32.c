#include <stdlib.h>
#include <peekpoke.h>

volatile const char c[32000] = {1, [31999] = 2};

int main(void) {
  if (c[0] != 1)
    return EXIT_FAILURE;
  if (c[31999] != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
