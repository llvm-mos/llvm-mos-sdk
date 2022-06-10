#include <stdio.h>
#include <stdlib.h>

extern unsigned char volatile __CHARBUF;

int getchar(void)
{
    do
    {
        asm volatile ("JSR\t__kbhit" ::: "p", "a", "x", "y");
    } while (!__CHARBUF);
    
    int const result = __CHARBUF;

    __CHARBUF = 0;

    return result;
}
