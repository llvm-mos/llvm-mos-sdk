typedef void (*func_ptr)(void);

extern func_ptr __fini_array_start[], __fini_array_end[];

void _fini(void) {
  for (func_ptr *func = __fini_array_start; func != __fini_array_end; func++)
    (*func)();
}
