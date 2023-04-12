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

int main(void)
{
    cx16_k_screen_mode_set(128);
    cx16_k_console_init(10, 10, 320-20, 240-20);
    cx16_k_console_put_char('\x92', 0);
    cx16_k_console_put_char('H', 0);
    cx16_k_console_put_char('e', 0);
    cx16_k_console_put_char('l', 0);
    cx16_k_console_put_char('l', 0);
    cx16_k_console_put_char('o', 0);
    cx16_k_console_put_char(' ', 0);
    cx16_k_console_put_char('C', 0);
    cx16_k_console_put_char('o', 0);
    cx16_k_console_put_char('m', 0);
    cx16_k_console_put_char('m', 0);
    cx16_k_console_put_char('a', 0);
    cx16_k_console_put_char('n', 0);
    cx16_k_console_put_char('d', 0);
    cx16_k_console_put_char('e', 0);
    cx16_k_console_put_char('r', 0);
    cx16_k_console_put_char(' ', 0);
    cx16_k_console_put_char('X', 0);
    cx16_k_console_put_char('1', 0);
    cx16_k_console_put_char('6', 0);
    cx16_k_console_put_char('!', 0);

    while (cbm_k_getin() == 0)
        ;

    cx16_k_console_put_image(face, 8, 8);   // TODO: Why does the screen clear?

    while (cbm_k_getin() == 0)
        ;

    cx16_k_screen_mode_set(0);
    putchar(15);             // ISO mode

    printf("Done\n");        // finished
}