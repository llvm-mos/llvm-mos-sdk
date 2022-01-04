#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERBOSE 1

#if VERBOSE
#define logva printf
#else
void logva(const char *s, ...) {}
#endif

int main() {
  static void *an_alloc = NULL;
  an_alloc = malloc(500);
  if (an_alloc != NULL) {
    logva("ALLOCATED 500 BYTES AT %p\n", an_alloc);
    free(an_alloc);
  }

  an_alloc = malloc(40000);
  if (!an_alloc) {
    puts("ALLOCATION FOR 40000 BYTES FAILED");
  } else {
    logva("ALLOCATED 40000 BYTES AT %p\n", an_alloc);
    free(an_alloc);
  }

#define ALLOC_COUNT 8

  static const size_t alloc_sizes[ALLOC_COUNT] = {1, 4, 16, 7, 35, 100, 3, 9};
  static uint8_t *allocations[ALLOC_COUNT] = {};

  for (uint8_t i = 0; i < ALLOC_COUNT; i += 1) {
    const uint8_t alloc_sz = alloc_sizes[i];
    uint8_t *const new_alloc = malloc(alloc_sz);
    if (new_alloc == NULL) {
      puts("ALLOCATION FAILED");
      return 1;
    }

    logva("ALLOCATED %u BYTES AT %p\n", (unsigned)alloc_sz, new_alloc);

    memset(new_alloc, (int)alloc_sz, alloc_sz);
    allocations[i] = new_alloc;
  }

  // dealloc in a different order than alloc
  static uint8_t dealloc_order[ALLOC_COUNT] = {4, 6, 2, 0, 3, 1, 7, 5};

  for (uint8_t i = 0; i < ALLOC_COUNT; i += 1) {
    const uint8_t test_alloc_idx = dealloc_order[i];
    uint8_t *const alloc_to_test = allocations[test_alloc_idx];
    const uint8_t test_alloc_size = alloc_sizes[test_alloc_idx];

    logva("CHECKING ALLOCATION OF %u BYTES AT %p\n", test_alloc_size,
          alloc_to_test);

    for (uint8_t j = 0; j < test_alloc_size; j += 1) {
      if (alloc_to_test[j] != test_alloc_size) {
        logva("UNEXPECTED VALUE STORED IN HEAP: EXPECT %u, ACTUAL %u\n",
              (unsigned)test_alloc_size, (unsigned)alloc_to_test[j]);
        return 1;
      }
    }

    free(alloc_to_test);
  }

  puts("MALLOC WORKS");
  return 0;
}
