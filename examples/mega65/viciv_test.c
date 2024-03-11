#include <mega65.h>

int main(void) {
  VICIV.screencol = COLOR_BUBBLEGUM;
  while (1) {
    VICIV.bordercol++;
  }
  return 0;
}
