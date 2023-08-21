#include <mega65.h>

int main() {
  VICIV.BG_COLOR = LIGHT_BLUE;
  while (true) {
    VICIV.BORDER_COLOR++;
  }
}
