// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

/*****************************************************************************/
/*                                                                           */
/*                                  _pbi.h                                   */
/*                                                                           */
/*                  Internal include file, do not use directly               */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2000 Freddy Offenga <taf_offenga@yahoo.com>                           */
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

#ifndef __PBI_H
#define __PBI_H

/* parallel bus interface area */
#define PBI             ((volatile unsigned char*)0xD100)

/* parallel device IRQ status */
#define PDVI            ((volatile unsigned char*)0xD1FF)

/* parallel device select */
#define PDVS            ((volatile unsigned char*)0xD1FF)

/* parallel bus interface RAM area */
#define PBIRAM          ((volatile unsigned char*)0xD600)

/* parallel device ID 1 */
#define PDID1           ((volatile unsigned char*)0xD803)

/* parallel device I/O vector */
#define PDIDV           ((volatile unsigned char*)0xD805)

/* parallel device IRQ vector */
#define PDIRQV          ((volatile unsigned char*)0xD808)

/* parallel device ID 2 */
#define PDID2           ((volatile unsigned char*)0xD80B)

/* parallel device vector table */
#define PDVV            ((volatile unsigned char*)0xD80D)

/* End of _pbi.h */
#endif /* #ifndef __PBI_H */
