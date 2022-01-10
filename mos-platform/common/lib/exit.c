#include <stdlib.h>
#include <stdio.h>

extern __attribute__((noreturn)) void __exit(int status);

void exit(int status) {
  __exit(status);
}
