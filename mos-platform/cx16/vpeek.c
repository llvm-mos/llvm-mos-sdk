#include <stdint.h>
#include <cx16.h>

uint8_t vpeek(const uint32_t address) {
  VERA.control = 0;
  VERA.address = (uint16_t)address;
  VERA.address_hi = (uint8_t)(address >> 16);
  return VERA.data0;
}
