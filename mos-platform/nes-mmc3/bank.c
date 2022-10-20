#include "bank.h"
#include "peekpoke.h"

__attribute__((section(".zp.bss"))) char __bank_select_hi;
__attribute__((section(".zp.bss"))) char __in_progress;
__attribute__((section(".zp.noinit"))) char __prg_8000;
__attribute__((section(".zp.noinit"))) char __prg_a000;

__attribute__((weak)) char get_prg_8000(void) { return __prg_8000; }
__attribute__((weak)) char get_prg_a000(void) { return __prg_a000; }

__attribute__((weak)) void set_chr_mode_0(char chr_id) {
  POKE(0x8000, __bank_select_hi | 0);
  POKE(0x8001, chr_id);
}

__attribute__((weak)) void set_chr_mode_1(char chr_id) {
  POKE(0x8000, __bank_select_hi | 1);
  POKE(0x8001, chr_id);
}

__attribute__((weak)) void set_chr_mode_2(char chr_id) {
  POKE(0x8000, __bank_select_hi | 2);
  POKE(0x8001, chr_id);
}

__attribute__((weak)) void set_chr_mode_3(char chr_id) {
  POKE(0x8000, __bank_select_hi | 3);
  POKE(0x8001, chr_id);
}

__attribute__((weak)) void set_chr_mode_4(char chr_id) {
  POKE(0x8000, __bank_select_hi | 4);
  POKE(0x8001, chr_id);
}

__attribute__((weak)) void set_chr_mode_5(char chr_id) {
  POKE(0x8000, __bank_select_hi | 5);
  POKE(0x8001, chr_id);
}

__attribute__((weak)) void set_mirroring(char mode) {
  POKE(0xa000, mode);
}

__attribute__((weak)) void set_wram_mode(char mode) {
  POKE(0xa001, mode);
}

__attribute__((weak)) void set_prg_mode(char mode) {
  __bank_select_hi = (__bank_select_hi & ~PRG_MODE_1) | mode;
}

__attribute__((weak)) void set_chr_a12_inversion(char mode) {
  __bank_select_hi = (__bank_select_hi & ~CHR_A12_INVERT) | mode;
}
