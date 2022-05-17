#ifndef _OSI_SCREEN_H
#define _OSI_SCREEN_H

#include <string.h>

template <
    unsigned int scr_base_uint = 0xD000, // start address of video RAM
    unsigned int video_ram_size = 0x400, // size of video RAM
    unsigned int screen_width = 0x1B, // screen width
    unsigned int screen_height = 0x1B, // screen height
    unsigned int screen_firstchar = 0x85, // offset of cursor position (0, 0) from base of video RAM
    unsigned int scroll_dist = 0x20 // memory distance for scrolling by one line
>
class osi_screen
{
private:
    static unsigned char cursor_x;
    static unsigned char cursor_y;

    static constexpr unsigned int scroll_length(void)
    {
        return (screen_height - 1) * scroll_dist;
    }

    static constexpr char *scr_base(void)
    {
        return (char *) scr_base_uint;
    }

    static char *cursor_pos_mem(void)
    {
        return scr_base() + screen_firstchar + cursor_y * scroll_dist + cursor_x;
    }

    static void newline(void)
    {
        cursor_y += 1;

        if (cursor_y == screen_height)
        {
            // Bottom of screen reached, scroll
            cursor_y -= 1;

            char * const scr_firstchar_addr = scr_base() + screen_firstchar;
            char * const scroll_dest = scr_firstchar_addr;
            char * const scroll_src = scr_firstchar_addr + scroll_dist;

            memmove(scroll_dest, scroll_src, scroll_length());

            // Address of first character in last line of screen
            char * const last_line_start = scr_firstchar_addr + scroll_length();

            // Fill last line with blanks
            memset(last_line_start, ' ', screen_width);
        }
    }

public:
    static void clrscr(void)
    {
        memset((void *) scr_base, ' ', video_ram_size);
        cursor_x = cursor_y = 0;
    }

    static void cputc(char c)
    {
        if (c == '\n')
        {
            newline();
        }
        else if (c == '\r')
        {
            cursor_x = 0;
        }
        else
        {
            char * const dest = cursor_pos_mem();
            *dest = c;
            if (cursor_x >= screen_width - 1)
            {
                newline();
                cursor_x = 0;
            }
            else
            {
                cursor_x += 1;
            }
        }
    }
};

extern "C" void __putchar(char c);

#endif // _OSI_SCREEN_H