typedef void (*func_ptr)(void);

extern func_ptr __init_array_start[], __init_array_end[];

void _init(void) {
  for (func_ptr *func = __init_array_start; func != __init_array_end; func++)
    (*func)();
}
