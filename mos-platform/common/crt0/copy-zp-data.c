#include <string.h>

asm(".global __do_copy_zp_data\n"
    ".section .init.200,\"axR\",@progbits\n"
    "__do_copy_zp_data:\n"
    "  jsr __copy_zp_data\n");

extern char __zp_data_start[];
extern void __zp_data_size;

extern char __zp_data_load_start[];

void __copy_zp_data(void) {
  memcpy(__zp_data_start, __zp_data_load_start,
         (unsigned short)&__zp_data_size);
}
