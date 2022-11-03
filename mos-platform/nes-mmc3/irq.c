#include "bank.h"

__attribute__((section(".zp.noinit"))) const void *__irq_ptr;
__attribute__((section(".zp.noinit"))) char __irq_index;
__attribute__((section(".zp.noinit"))) char __irq_done;

const char default_array[] = {0xff};

asm(".globl __bank_nmi\n");

void __disable_irq(void) {
  __attribute__((leaf)) asm("sta $e000\n");
  set_irq_ptr(default_array);
}
__attribute__((weak, alias("__disable_irq"))) void disable_irq(void);

__attribute__((weak)) void set_irq_ptr(const void *address) {
  __irq_ptr = address;
}

__attribute__((weak)) char is_irq_done(void) { return __irq_done; }
