#include <stdlib.h>

volatile const char pad_fixed[20000] = {3, [19999] = 4};

__attribute__((section(".dpcm"))) volatile const char dpcm[64] = {
    1, [63] = 2};

int main(void) {
  if (((unsigned) dpcm) & 0x3f)
    return EXIT_FAILURE;
  if (((unsigned) dpcm) < 0xc000)
    return EXIT_FAILURE;
  if (pad_fixed[0] != 3 || pad_fixed[19999] != 4)
    return EXIT_FAILURE;
  if (dpcm[0] != 1 || dpcm[63] != 2)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
