#include <mega65.h>

int main(void) {
  VICIV.screencol = COLOR_LIGHTBLUE;
  while (1) {
    VICIV.bordercol++;
  }
  return 0;
}
