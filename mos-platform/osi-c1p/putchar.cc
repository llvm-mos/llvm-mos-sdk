#include "osi_screen.h"

template<unsigned int scr_base_int, unsigned int video_ram_size,
    unsigned int screen_width, unsigned int screen_height,
    unsigned int screen_firstchar, unsigned int scroll_dist>
    unsigned char
    __osi_screen<scr_base_int, video_ram_size, screen_width, screen_height,
         screen_firstchar, scroll_dist>::cursor_x;

template<unsigned int scr_base_int, unsigned int video_ram_size,
    unsigned int screen_width, unsigned int screen_height,
    unsigned int screen_firstchar, unsigned int scroll_dist>
    unsigned char
    __osi_screen<scr_base_int, video_ram_size, screen_width, screen_height,
         screen_firstchar, scroll_dist>::cursor_y;

using __osic1p_screen = __osi_screen<>;

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
    /*
     * The low-level character output function implements LF as line feed
     * without CR, e.g. the active position stays in the same column. Here we
     * implement the C standard semantics where \n moves the active position
     * to the initial position of the next line.
     */ 
    if (c == '\n')
    {
        __osic1p_screen::cputc('\r');
    }

    __osic1p_screen::cputc(c);
}

/**
 * @brief __clrscr clear the screen
 */
extern "C"
void __clrscr(void)
{
    __osic1p_screen::clrscr();
}
