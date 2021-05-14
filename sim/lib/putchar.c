#include <stdio.h>

void __putchar(char c) {
  // Writing to this IO register causes the simulator to print the written byte
  // as a character to stdout.
  (*(char *)0xFFF9) = c;
}