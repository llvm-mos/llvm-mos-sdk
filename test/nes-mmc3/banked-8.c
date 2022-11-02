#include <bank.h>
#include <stdlib.h>

volatile const char large_array[0x5000] = {
    [0] = 1, [0x2000] = 2, [0x4000] = 3, [0x4fff] = 4};

__attribute__((section(".prg_rom_0"))) volatile const char bank_0[0x2000] = {
    [0] = 1, [0x1fff] = 2};
__attribute__((section(".prg_rom_1"))) volatile const char bank_1[0x2000] = {
    [0] = 3, [0x1fff] = 4};

int main(void) {
  if ((unsigned)large_array < 0xa000)
    return EXIT_FAILURE;
  if (large_array[0] != 1)
    return EXIT_FAILURE;
  if (large_array[0x2000] != 2)
    return EXIT_FAILURE;
  if (large_array[0x4000] != 3)
    return EXIT_FAILURE;
  if (large_array[0x4fff] != 4)
    return EXIT_FAILURE;

  if ((unsigned) bank_0 >= 0xa000)
    return EXIT_FAILURE;
  set_prg_8000(0);
  if (bank_0[0] != 1)
    return EXIT_FAILURE;
  if (bank_0[0x1fff] != 2)
    return EXIT_FAILURE;

  if ((unsigned) bank_1 >= 0xa000)
    return EXIT_FAILURE;
  set_prg_bank(1, (unsigned)bank_1 >> 8);
  if (bank_1[0] != 3)
    return EXIT_FAILURE;
  if (bank_1[0x1fff] != 4)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
