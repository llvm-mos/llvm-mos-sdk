// llvm-mos-sdk cx16 kernel test
//
// vim: set et ts=4 sw=4

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cbm.h>
#include <cx16.h>

unsigned char face[64] = {1, 1, 1, 1, 1, 1, 1, 1,
                          1, 1, 0, 0, 0, 0, 1, 1,
                          1, 0, 5, 0, 0, 5, 0, 1,
                          1, 0, 0, 0, 0, 0, 0, 1,
                          1, 0, 1, 0, 0, 1, 0, 1,
                          1, 0, 0, 1, 1, 0, 0, 1,
                          1, 1, 0, 0, 0, 0, 1, 1,
                          1, 1, 1, 1, 1, 1, 1, 1
                         };

void wait_key(void)
{
    while (cbm_k_getin() == 0)
        ;
}

void graph_put_string(unsigned int x, unsigned int y, const char *str)
{
    graph_pos_t pos;
    pos.x = x;
    pos.y = y;
    uint8_t c = 0;
    while ((c = *str++) != 0)
    {
        cx16_k_graph_put_char(&pos, c);
    }
}

int main(void)
{
    uint8_t scolor = 1;             // stroke color
    int16_t xpos = 160, ypos = 120; // initial face position
    int8_t xd = 1;                  // initial face direction

    // set 320x240x8-bpp
    cx16_k_screen_mode_set(128);

    // init default graphics driver
    cx16_k_graph_init(0);

    // default font
    cx16_k_graph_set_font(0);

    // draw outline box
    cx16_k_graph_set_colors(4, 0, 0);
    cx16_k_graph_draw_line(10, 10, 320 - 10, 10);
    cx16_k_graph_draw_line(320 - 10, 10, 320 - 10, 240 - 10);
    cx16_k_graph_draw_line(320 - 10, 240 - 10, 10, 240 - 10);
    cx16_k_graph_draw_line(10, 240 - 10, 10, 10);

    // welcome message
    cx16_k_graph_set_colors(0, 0, 0);
    graph_put_string(75, 20, "Hello Commander X16 and llvm-mos!\n\n              Basic cx16_k_graph* wrapper test...");

    // window clipping test
    cx16_k_graph_set_window(0, 0, 320 / 2, 240);
    cx16_k_graph_set_colors(4, 0, 0);
    graph_put_string(50, 60, "This text is using clipping to draw in two colors.");
    cx16_k_graph_set_window(320 / 2, 0, 320 / 2, 240);
    cx16_k_graph_set_colors(5, 0, 0);
    graph_put_string(50, 60, "This text is using clipping to draw in two colors.");

    // full screen window
    cx16_k_graph_set_window(0, 0, 0, 0);

    // draw outline rectangle
    cx16_k_graph_set_colors(6, 0, 0);
    cx16_k_graph_draw_rect(50, 50, 42, 14, 0, 0);
    // move (copy) rectangle
    cx16_k_graph_move_rect(50, 50, 65, 65, 42, 15);

    // label moved rectangle
    cx16_k_graph_set_colors(0, 0, 0);
    graph_put_string(110, 75, "<- rectangle moved here");

    // stop message
    graph_put_string(110, 240 - 20, "Press a key to stop");

    // until a key is pressed, bounce face and rectangle
    while (cbm_k_getin() == 0)
    {
        // draw 8x8 "face" image
        cx16_k_graph_draw_image(xpos, ypos, face, 8, 8);

        // update x position
        xpos += xd;

        // if near edges, reverse direction
        if (xpos < 64 || xpos > 320 - 64)
        {
            xd = -xd;
        }

        // draw filled rectangle offset from face using incrementing color
        scolor += 1;
        cx16_k_graph_set_colors(scolor, scolor + 1, 0);
        cx16_k_graph_draw_rect(xpos - 12, ypos + 20, 8, 16, 0, 1);

        waitvsync();
    }

    // erase old message
    cx16_k_graph_set_colors(1, 1, 1);
    cx16_k_graph_draw_rect(20, 240 - 20 - 10, 280, 20, 0, 1);

    // exit message
    cx16_k_graph_set_colors(0, 0, 0);
    graph_put_string(110, 240 - 20, "Press a key to exit");

    // wait for final key press
    wait_key();

    // restore 80x60 text mode
    cx16_k_screen_mode_set(0);

    // done message
    printf("DONE.\n");
}
