// llvm-mos-sdk cx16 kernel test
//
// vim: set et ts=4 sw=4

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cbm.h>
#include <cx16.h>

unsigned char face[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 1, 1,
    1, 0, 1, 0, 0, 1, 0, 1,
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

void console_puts(const char *str, unsigned char wordwrap)
{
    uint8_t c = 0;
    while ((c = *str++) != 0)
    {
        cx16_k_console_put_char(c, wordwrap);
    }
}

int main(void)
{
    cx16_k_screen_mode_set(128);
    cx16_k_graph_set_colors(1, 0, 0);
    cx16_k_console_init(0, 0, 0, 0);
    console_puts("\x92Hello Commander X16!", 0);

    wait_key();

    // BUG: I don't understand why this clears/scrolls screen...
    cx16_k_console_put_image(face, 8, 8);

    wait_key();

    cx16_k_screen_mode_set(0);
    printf("DONE.\n");
}
