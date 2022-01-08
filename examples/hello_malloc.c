#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  static void *an_alloc = NULL;
  an_alloc = malloc(500);
  if (an_alloc != NULL) {
    printf("ALLOCATED 500 BYTES AT %p\n", an_alloc);

    memset(an_alloc, 42, 500);

    free(an_alloc);
  }

  an_alloc = malloc(40000);
  if (!an_alloc) {
    puts("ALLOCATION FOR 40000 BYTES FAILED");
  } else {
    printf("ALLOCATED 40000 BYTES AT %p\n", an_alloc);
    free(an_alloc);
  }

  return 0;
}
