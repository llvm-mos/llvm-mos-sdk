#include "peekpoke.h"
#include "mapper.h"

__attribute__((section(".zp.bss"))) char __current_bank;

__attribute__((weak)) char get_current_bank(void) { return __current_bank; }

__attribute__((weak)) void bank_select(char bank_id) {
  POKE(0x3f, bank_id);
  __current_bank = bank_id;
}

__attribute__((weak)) void ram_select(char bank_id) {
  POKE(0x3e, bank_id);
  __current_bank = bank_id | 0x80;
}

__attribute__((weak)) void xram_write(int address, char value) {
  POKE(0x1400 + (address & 0x3ff), value);
}

__attribute__((weak)) unsigned char xram_read(int address) {
  return PEEK(0x1000 + (address & 0x3ff));
}
