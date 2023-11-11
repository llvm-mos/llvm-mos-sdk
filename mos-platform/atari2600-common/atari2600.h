// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version (added volatile).

/*****************************************************************************/
/*                                                                           */
/* Atari VCS 2600 TIA & RIOT registers addresses                             */
/*                                                                           */
/* Source: DASM Version 1.05 - vcs.h                                         */
/*                                                                           */
/* Florent Flament (contact@florentflament.com), 2017                        */
/*                                                                           */
/*****************************************************************************/


#ifndef _ATARI2600_H
#define _ATARI2600_H

#ifdef __cplusplus
extern "C" {
#endif

#include <_tia.h>
#define TIA (*(volatile struct __tia*)0x0000)

#include <_riot.h>
#define RIOT (*(volatile struct __riot*)0x0280)

#include <atari2600_constants.h>

#ifdef __cplusplus
}
#endif

/* End of atari2600.h */
#endif
