#include <stdlib.h>

typedef void (*func_ptr)(void);

extern func_ptr __init_array_start[0], __init_array_end[0];
extern func_ptr __fini_array_start[0], __fini_array_end[0];

static void __invoke_all(func_ptr * array_start, func_ptr * array_end) {
  for (func_ptr *func = array_start; func != array_end; func++)
    (*func)();
}

void _init(void) {
    __invoke_all(__init_array_start, __init_array_end);
}

void _fini(void) {
    __invoke_all(__fini_array_start, __fini_array_end);
}

extern int main();

void __init_main() {
    _init();
    exit(main());
}
