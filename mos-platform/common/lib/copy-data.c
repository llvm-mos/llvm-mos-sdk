#include <string.h>

asm(
  ".global __do_copy_data\n"
  ".section .init.20,\"axR\",@progbits\n"
  "__do_copy_data:\n"
  "  jsr __copy_data\n"
);

extern char __data_start[];
extern char __data_end[];

extern char __data_load_start[];

void __copy_data(void) {
  memcpy(__data_start, __data_load_start, __data_end - __data_start);
}
