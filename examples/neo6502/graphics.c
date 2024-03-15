#include <neo/api.h>

static uint8_t rectangle_colors[] = {9, 12, 13, 1, 11, 15, 3, 7};

int main(void) {
  neo_console_clear_screen();
  for (int i = 0; i < sizeof(rectangle_colors); i++) {
    neo_graphics_set_color(rectangle_colors[i]);
    neo_graphics_draw_rectangle(20 + i, 20 + i, 300 - i, 220 - i);
  }

  neo_graphics_set_color(4);
  neo_graphics_draw_ellipse(70, 30, 250, 210);

  neo_graphics_set_draw_size(3);
  for (int i = 0; i < 2; i++) {
    neo_graphics_set_color(9 - 2*i);
    uint16_t center_x = (320 - (6 * 8) * 3) / 2;
    uint16_t center_y = (240 - (8 * 2) * 3) / 2;
    neo_graphics_draw_text(center_x-i, center_y-i, "Hello,");
    neo_graphics_draw_text(center_x-i, center_y-i+8*3, "Neo6502!");
  }

  neo_graphics_set_draw_size(1);
  neo_graphics_set_color(14);
  neo_graphics_draw_text(290 - (6 * 10), 202, "- LLVM-MOS");

  return 0;
}
