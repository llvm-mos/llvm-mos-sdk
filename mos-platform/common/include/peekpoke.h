// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

// clang-format off

/*****************************************************************************/
/*                                                                           */
/*                                peekpoke.h                                 */
/*                                                                           */
/*     PEEK and POKE macros for those who want to write BASIC code in C      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2003      Ullrich von Bassewitz                                       */
/*               Roemerstrasse 52                                            */
/*               D-70794 Filderstadt                                         */
/* EMail:        uz@cc65.org                                                 */
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



#ifndef _PEEKPOKE_H
#define _PEEKPOKE_H



/*****************************************************************************/
/*                                  Macros                                   */
/*****************************************************************************/



#define POKE(addr,val)     (*(volatile unsigned char*) (addr) = (val))
#define POKEW(addr,val)    (*(volatile unsigned*) (addr) = (val))
#define PEEK(addr)         (*(volatile unsigned char*) (addr))
#define PEEKW(addr)        (*(volatile unsigned*) (addr))



/* End of peekpoke.h */
#endif
