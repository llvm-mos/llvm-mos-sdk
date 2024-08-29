#include <cbm.h>
#include <stdint.h>

void *cbm_k_load(const unsigned char verifyflag, const void *startaddr) {

  const uint16_t addr = (uint16_t)(startaddr);

  union {
    uint16_t word;
    struct {
      uint8_t lo, hi;
    };
  } result;

  __attribute__((leaf)) __asm__ volatile(
      "    jsr __LOAD   \n"
      "    bsr 1f       \n" // carry-clear = no error
      "    tax          \n" // get error code from A
      "    ldy #0       \n"
      "1:               \n" // no errror
      : "=x"(result.lo), "=y"(result.hi)
      : "a"(verifyflag), "x"((uint8_t)(addr)), "y"((uint8_t)(addr >> 8))
      : "p");

  return (void *)(result.word);
}
