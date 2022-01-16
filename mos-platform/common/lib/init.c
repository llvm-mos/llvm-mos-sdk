#include <stdlib.h>

typedef void (*func_ptr)(void);

extern func_ptr _init_array_start[0], _init_array_end[0];
extern func_ptr _fini_array_start[0], _fini_array_end[0];

static void __invoke_all(func_ptr * array_begin, func_ptr * array_end) {
  for (func_ptr *func = array_begin; func != array_end; func++)
    (*func)();
}

void __init(void) {
    __invoke_all(_init_array_start, _init_array_end);
}

void __fini(void) {
    __invoke_all(_fini_array_start, _fini_array_end);
}

extern int main();

void __init_main() {
    __init();
    exit(main());
}
