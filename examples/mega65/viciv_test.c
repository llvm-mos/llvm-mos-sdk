#include <mega65.h>
#include <stdbool.h>

int main(void) {
  VICIV.screencol = COLOR_LIGHTBLUE;
  while (true) {
    VICIV.bordercol++;
  }
  return 0;
}
