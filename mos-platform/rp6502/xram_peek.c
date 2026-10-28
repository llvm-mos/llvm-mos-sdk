#include "rp6502.h"

unsigned char xram0_peek8(unsigned addr) {
  RIA.addr0 = addr;
  return RIA.rw0;
}

unsigned char xram1_peek8(unsigned addr) {
  RIA.addr1 = addr;
  return RIA.rw1;
}

unsigned xram0_peek16(unsigned addr) {
  RIA.addr0 = addr;
  RIA.step0 = 1;
  unsigned char lo = RIA.rw0;
  return lo | (unsigned)RIA.rw0 << 8;
}

unsigned xram1_peek16(unsigned addr) {
  RIA.addr1 = addr;
  RIA.step1 = 1;
  unsigned char lo = RIA.rw1;
  return lo | (unsigned)RIA.rw1 << 8;
}
