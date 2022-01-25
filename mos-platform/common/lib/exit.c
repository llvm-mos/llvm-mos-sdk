#include <stdlib.h>
#include <stdio.h>

__attribute__((weak)) void __call_atexit(void);

__attribute__((noreturn)) void _exit(int status);
void _fini();

void exit(int status) {
  _fini();
  if (__call_atexit)
    __call_atexit();
  _exit(status);
}
