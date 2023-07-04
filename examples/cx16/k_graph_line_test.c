// llvm-mos-sdk cx16 kernel test
//
// vim: set et ts=4 sw=4

#include <stddef.h>
#include <stdint.h>

#include <cbm.h>
#include <cx16.h>

int main(void)
{
    int16_t x, y;
    uint8_t c;

    cx16_k_screen_mode_set(128);        // 320x240x8-bpp
    cx16_k_graph_init(NULL);            // initialize kernal graph with defaults
    c = 0;                              // initialize color

    // draw line pattern
    for (y = 0; y < 240; y += 3)
    {
        cx16_k_graph_set_colors(c++, 0, 0);
        cx16_k_graph_draw_line(0, y, 319, 239 - y);
    }

    for (x = 0; x < 320; x += 3)
    {
        cx16_k_graph_set_colors(c++, 0, 0);
        cx16_k_graph_draw_line(x, 0, 319 - x, y);
    }

    while (cbm_k_getin() == 0)        // wait for a keypress
        ;

    cx16_k_screen_mode_set(0);        // reset screen mode to 80x30
}
