typedef void (*func_ptr)(void);

extern func_ptr __fini_array_start[], __fini_array_end[];

asm(".section .fini.200,\"axR\",@progbits\n"
    "jsr __do_fini_array\n");

void __do_fini_array(void) {
  for (func_ptr *func = __fini_array_start; func != __fini_array_end; func++)
    (*func)();
}
