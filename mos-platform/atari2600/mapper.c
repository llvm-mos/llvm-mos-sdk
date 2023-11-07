#include "peekpoke.h"
#include "mapper.h"

__attribute__((weak)) void set_current_bank(char bank_id) {
  if (bank_select && !(bank_id & 0x80)) {
    bank_select(bank_id);
  } else if (ram_select) {
    ram_select(bank_id & 0x7f);
  }
}

__attribute__((weak, callback(2))) void banked_call_rom(char bankId,
                                                        void (*method)(void)) {
  char previous_bank_id = get_current_bank();
  bank_select(bankId);
  method();
  set_current_bank(previous_bank_id);
}

__attribute__((weak, callback(2))) void banked_call_ram(char bankId,
                                                        void (*method)(void)) {
  char previous_bank_id = get_current_bank();
  ram_select(bankId);
  method();
  set_current_bank(previous_bank_id);
}

