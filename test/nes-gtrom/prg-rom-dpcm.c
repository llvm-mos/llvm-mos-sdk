#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

volatile const char pad_fixed[5000] = {1, [4999] = 2};

__attribute__((section(".prg_rom_0.rodata"))) volatile const char pad_0[15000] = {
    3, [14999] = 4};
__attribute__((section(".dpcm_0"))) volatile const char dpcm_0[64] = {
    9, [63] = 10};
__attribute__((section(".dpcm_15"))) volatile const char dpcm_15[64] = {
    11, [63] = 12};

int main(void) {
  // Check section alignment.
  if (((unsigned) dpcm_0) & 0x3f)
    return EXIT_FAILURE;
  if (((unsigned) dpcm_15) & 0x3f)
    return EXIT_FAILURE;

  // Check section location.
  if (((unsigned) dpcm_0) < 0xc000)
    return EXIT_FAILURE;
  if (((unsigned) dpcm_15) < 0xc000)
    return EXIT_FAILURE;

  if (pad_fixed[0] != 1 || pad_fixed[4999] != 2)
    return EXIT_FAILURE;

  set_prg_bank(0);
  if (pad_fixed[0] != 1 || pad_fixed[4999] != 2)
    return EXIT_FAILURE;
  if (pad_0[0] != 3 || pad_0[14999] != 4)
    return EXIT_FAILURE;
  if (dpcm_0[0] != 9 || dpcm_0[63] != 10)
    return EXIT_FAILURE;

  set_prg_bank(15);
  if (pad_fixed[0] != 1 || pad_fixed[4999] != 2)
    return EXIT_FAILURE;
  if (dpcm_15[0] != 11 || dpcm_15[63] != 12)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
