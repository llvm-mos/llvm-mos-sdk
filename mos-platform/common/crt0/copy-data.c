#include <string.h>

asm(".global __do_copy_data\n"
    ".section .init.200,\"axR\",@progbits\n"
    "__do_copy_data:\n"
    "  jsr __copy_data\n");

extern char __data_start[];
extern void __data_size;

extern char __data_load_start[];

void __copy_data(void) {
  memcpy(__data_start, __data_load_start, (unsigned short)&__data_size);
}
