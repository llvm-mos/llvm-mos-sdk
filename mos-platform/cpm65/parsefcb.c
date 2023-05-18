/* Parses an FCB from a filename.
 *
 * © 2023 David Given
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE
 * file in the project root for the full text.
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <cpm.h>

static const char* fill(uint8_t* dest, const char* src, int len)
{
    do
    {
        char c = toupper(*src);
        if (!c || (c == '.'))
            c = ' ';
        else if (c == '*')
            c = '?';
        else
            src++;
        *dest++ = c;
    }
    while (--len);
    return src;
}

uint8_t cpm_parse_filename(FCB* fcb, const char* filename)
{
	for (uint8_t i=0; i<sizeof(FCB); i++)
		((uint8_t*)fcb)[i] = 0;
	for (uint8_t i=0; i<sizeof(fcb->f); i++)
		fcb->f[i] = ' ';

	if (filename[0] && (filename[1] == ':'))
    {
            uint8_t c = filename[0];
            c = toupper(c);
            if (!isalpha(c))
				return true;
			c -= '@';
			if ((c < 'A') || (c > 'P'))
				return true;

                fcb->dr = c;

            filename += 2;
    }

    /* Read filename part. */

    filename = fill(&fcb->f[0], filename, 8);
    filename = strchr(filename, '.');
    if (filename)
        fill(&fcb->f[8], filename+1, 3);

    if (fcb->dr == 0)
        fcb->dr = cpm_get_current_drive() + 1;
	return false;
}

