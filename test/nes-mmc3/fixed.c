#include <mapper.h>
#include <stdlib.h>

volatile const char large_array[0x7000] = {
    [0] = 1, [0x2000] = 2, [0x4000] = 3, [0x6000] = 4, [0x6fff] = 5};

int main(void) {
  if (large_array[0] != 1)
    return EXIT_FAILURE;
  if (large_array[0x2000] != 2)
    return EXIT_FAILURE;
  if (large_array[0x4000] != 3)
    return EXIT_FAILURE;
  if (large_array[0x6000] != 4)
    return EXIT_FAILURE;
  if (large_array[0x6fff] != 5)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
