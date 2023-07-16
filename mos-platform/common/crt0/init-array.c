typedef void (*func_ptr)(void);

extern func_ptr __init_array_start[], __init_array_end[];

asm(".section .init.300,\"axR\",@progbits\n"
    "jsr __do_init_array");

void __do_init_array(void) {
  for (func_ptr *func = __init_array_start; func != __init_array_end; func++)
    (*func)();
}
