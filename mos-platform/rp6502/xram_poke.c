#include "rp6502.h"

void xram0_poke8(unsigned addr, unsigned char val) {
  RIA.addr0 = addr;
  RIA.rw0 = val;
}

void xram1_poke8(unsigned addr, unsigned char val) {
  RIA.addr1 = addr;
  RIA.rw1 = val;
}

void xram0_poke16(unsigned addr, unsigned val) {
  RIA.addr0 = addr;
  RIA.step0 = 1;
  RIA.rw0 = val;
  RIA.rw0 = val >> 8;
}

void xram1_poke16(unsigned addr, unsigned val) {
  RIA.addr1 = addr;
  RIA.step1 = 1;
  RIA.rw1 = val;
  RIA.rw1 = val >> 8;
}
