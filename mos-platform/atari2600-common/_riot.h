// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65.

/*****************************************************************************/
/*                                                                           */
/* Atari VCS 2600 RIOT registers addresses                                   */
/*                                                                           */
/* Source: DASM - vcs.h                                                      */
/*                                                                           */
/* Florent Flament (contact@florentflament.com), 2017                        */
/*                                                                           */
/*****************************************************************************/

/* RIOT registers */
struct __riot {
    unsigned char swcha;
    unsigned char swacnt;
    unsigned char swchb;
    unsigned char swbcnt;
    unsigned char intim;
    unsigned char timint;

    unsigned char unused[14];

    unsigned char tim1t;
    unsigned char tim8t;
    unsigned char tim64t;
    unsigned char t1024t;
};
