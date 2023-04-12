// llvm-mos-sdk cx16 kernel test
//
// vim: set et ts=4 sw=4

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cbm.h>
#include <cx16.h>

unsigned char face[64] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 5, 0, 0, 5,
                          0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1,
                          1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

uint8_t scolor;
int16_t xpos = 320 / 5, ypos = 240 / 3;
int8_t  xd = 1;

graph_pos_t pos;

int main(void)
{
    cx16_k_screen_mode_set(128);
    cx16_k_graph_init(0);

    do
    {
        cx16_k_graph_set_colors(0, 0, 0);

        pos.x = 75;
        pos.y = 20;

        cx16_k_graph_put_char(&pos, 'H');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'e');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'l');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'l');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'o');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, ' ');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'C');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'o');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'm');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'm');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'a');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'n');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'd');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'e');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'r');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, ' ');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, 'X');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, '1');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, '6');
        pos.x += 8;
        cx16_k_graph_put_char(&pos, '!');

        cx16_k_graph_draw_line(0, 0, 319, 239);
        cx16_k_graph_draw_line(319, 0, 0, 239);

        cx16_k_graph_set_colors(scolor++, 0, 0);

        cx16_k_graph_draw_line(0, 0, 319, 0);
        cx16_k_graph_draw_line(319, 0, 319, 239);
        cx16_k_graph_draw_line(319, 239, 0, 239);
        cx16_k_graph_draw_line(0, 239, 0, 0);

        cx16_k_graph_set_colors(1, 1, 0);
        cx16_k_graph_draw_rect(xpos, ypos, 8, 8, 0, 1);
        xpos += xd;

        if (xpos < (0 + 16))
        {
            xd = 1;
        }

        if (xpos > (320 - 16))
        {
            xd = -1;
        }

        cx16_k_graph_draw_image(xpos, ypos, face, 8, 8);

    } while (cbm_k_getin() == 0);
    cx16_k_screen_mode_set(0);
}