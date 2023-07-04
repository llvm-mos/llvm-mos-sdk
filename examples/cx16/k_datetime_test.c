// llvm-mos-sdk cx16 kernel test
//
// vim: set et ts=4 sw=4

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cbm.h>
#include <cx16.h>

static void hexdump(const void *ptr, size_t bytes)
{
    uint8_t *p = (uint8_t *)ptr;
    for (size_t i = 0; i < bytes; i++)
    {
        if ((i & 0xf) == 0)
        {
            if (i)
            {
                printf("\n");
            }
            printf("%04x: ", i);
        }
        else
        {
            printf(", ");
        }
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main(void)
{
    static cx16_date_time_t tm;

    putchar(15); // ISO mode
    printf("llvm-mos-sdk CX16 Kernal Test\n\n");

    printf("\ncx16_k_clock_get_date_time(&tm);\n");
    cx16_k_clock_get_date_time(&tm);

    printf("Result: year=%d, mon=%d, day=%d, hour=%d, min=%d, sec=%d, jif=%d\n",
           1900 + tm.year,
           tm.mon,
           tm.day,
           tm.hour,
           tm.min,
           tm.sec,
           tm.jif);
    hexdump(&tm, sizeof(tm));

    printf("\ncx16_k_clock_set_date_time(2023-1900, 4, 5, 10, 12, 13, 42);\n");
    cx16_k_clock_set_date_time(2023 - 1900, 4, 5, 10, 12, 13, 42);

    cx16_k_clock_get_date_time(&tm);

    printf("Result: year=%d, mon=%d, day=%d, hour=%d, min=%d, sec=%d, jif=%d\n",
           1900 + tm.year,
           tm.mon,
           tm.day,
           tm.hour,
           tm.min,
           tm.sec,
           tm.jif);
    hexdump(&tm, sizeof(tm));

    printf("Done\n"); // finished
}
