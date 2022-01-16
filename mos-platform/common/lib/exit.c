#include <stdlib.h>
#include <stdio.h>

extern __attribute__((noreturn)) void __exit(int status);
extern void __fini();

void exit(int status) {
  __fini();
  __exit(status);
}
