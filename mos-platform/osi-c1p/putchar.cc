#include "osi_screen.h"

// static c1p_screen screen_impl;
template<unsigned int scr_base_int, unsigned int video_ram_size,
    unsigned int screen_width, unsigned int screen_height,
    unsigned int screen_firstchar, unsigned int scroll_dist>
    unsigned char
    osi_screen<scr_base_int, video_ram_size, screen_width, screen_height,
         screen_firstchar, scroll_dist>::cursor_x;

template<unsigned int scr_base_int, unsigned int video_ram_size,
    unsigned int screen_width, unsigned int screen_height,
    unsigned int screen_firstchar, unsigned int scroll_dist>
    unsigned char
    osi_screen<scr_base_int, video_ram_size, screen_width, screen_height,
         screen_firstchar, scroll_dist>::cursor_y;

using c1p_screen = osi_screen<>;

/**
 * @brief __putchar implementation for Challenger 1P
 * 
 * For other screen layouts this module must be overridden.
 * 
 * @param c 
 */
extern "C"
void __putchar(char c)
{
    c1p_screen::cputc(c);
}
