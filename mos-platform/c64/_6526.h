// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Originally from cc65.

/*****************************************************************************/
/*                                                                           */
/*                                  _6526.h                                  */
/*                                                                           */
/*                Internal include file, do not use directly                 */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 1998-2000 Ullrich von Bassewitz                                       */
/*               Wacholderweg 14                                             */
/*               D-70597 Stuttgart                                           */
/* EMail:        uz@musoftware.de                                            */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



#ifndef __6526_H
#define __6526_H



/* Define a structure with the 6526 register offsets.
** NOTE: The timer registers are not declared as 16 bit registers, because
** the order in which the two 8 bit halves are written is important, and
** the compiler doesn't guarantee any order when writing 16 bit values.
*/
struct __6526 {
    unsigned char       pra;            /* Port register A */
    unsigned char       prb;            /* Port register B */
    unsigned char       ddra;           /* Data direction register A */
    unsigned char       ddrb;           /* Data direction register B */
    unsigned char       ta_lo;          /* Timer A, low byte */
    unsigned char       ta_hi;          /* Timer A, high byte */
    unsigned char       tb_lo;          /* Timer B, low byte */
    unsigned char       tb_hi;          /* Timer B, high byte */
    unsigned char       tod_10;         /* TOD, 1/10 sec. */
    unsigned char       tod_sec;        /* TOD, seconds */
    unsigned char       tod_min;        /* TOD, minutes */
    unsigned char       tod_hour;       /* TOD, hours */
    unsigned char       sdr;            /* Serial data register */
    unsigned char       icr;            /* Interrupt control register */
    unsigned char       cra;            /* Control register A */
    unsigned char       crb;            /* Control register B */
};



/* End of _6526.h */
#endif


