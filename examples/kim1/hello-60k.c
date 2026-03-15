// KIM-1 Hello World (expanded 60K RAM)
// Uses printf — plenty of room in the expanded variant.

#include <stdio.h>

int main(void) {
  printf("HELLO FROM KIM-1!\n");

  for (int i = 1; i <= 10; i++) {
    printf("COUNT: %d\n", i);
  }

  return 0;
}
