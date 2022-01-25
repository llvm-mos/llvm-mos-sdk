#include <stdlib.h>

__attribute__((weak)) void _init(void);
int main();

void __init_main() {
  if (_init)
    _init();
  exit(main());
}
