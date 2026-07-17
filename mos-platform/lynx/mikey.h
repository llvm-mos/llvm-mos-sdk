// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

#ifndef __MIKEY_H
#define __MIKEY_H

#ifdef __cplusplus
extern "C" {
#endif

/* timer structure */
typedef struct _mikey_timer {
  unsigned char reload;
  unsigned char control;
  unsigned char count;
  unsigned char control2;
} _mikey_timer;

typedef struct _mikey_all_timers {
  struct _mikey_timer timer[8];
} _mikey_all_timers;

/* audio channel structure */
typedef struct _mikey_audio {
  unsigned char volume;
  unsigned char feedback;
  unsigned char dac;
  unsigned char shiftlo;
  unsigned char reload;
  unsigned char control;
  unsigned char count;
  unsigned char other;
} _mikey_audio;

/* Define a structure with the mikey register offsets */
struct __mikey {
  struct _mikey_timer timer0;       // 0xFD00
  struct _mikey_timer timer1;       // 0xFD04
  struct _mikey_timer timer2;       // 0xFD08
  struct _mikey_timer timer3;       // 0xFD0C
  struct _mikey_timer timer4;       // 0xFD10
  struct _mikey_timer timer5;       // 0xFD14
  struct _mikey_timer timer6;       // 0xFD18
  struct _mikey_timer timer7;       // 0xFD1C
  struct _mikey_audio channel_a;    // 0xFD20
  struct _mikey_audio channel_b;    // 0xFD28
  struct _mikey_audio channel_c;    // 0xFD30
  struct _mikey_audio channel_d;    // 0xFD38
  unsigned char     attena;         // 0xFD40  ?? not yet allocated?
  unsigned char     attenb;         // 0xFD41      |
  unsigned char     attenc;         // 0xFD42      |
  unsigned char     attend;         // 0xFD43      |
  unsigned char     panning;        // 0xFD44      |
  unsigned char     unused0[11];    // 0xFD45 - 0xFD4F  not used
  unsigned char     mstereo;        // 0xFD50  stereo control bits
  unsigned char     unused1[47];    // 0xFD51 - 0xFD7F  not used
  unsigned char     intrst;         // 0xFD80  interrupt poll 0
  unsigned char     intset;         // 0xFD81  interrupt poll 1
  unsigned char     unused2[2];     // 0xFD82 - 0xFD83  not used
  unsigned char     magrdy0;        // 0xFD84  mag tape channel0 ready bit
  unsigned char     magrdy1;        // 0xFD85  mag tape channel1 ready bit
  unsigned char     audin;          // 0xFD86  audio in
  unsigned char     sysctl1;        // 0xFD87  control bits
  unsigned char     mikeyrev;       // 0xFD88  mikey hardware rev
  unsigned char     mikeysrev;      // 0xFD89  mikey software rev
  unsigned char     iodir;          // 0xFD8A  parallel i/o data dir
  unsigned char     iodat;          // 0xFD8B  parallel data
  unsigned char     serctl;         // 0xFD8C  serial control register
  unsigned char     serdat;         // 0xFD8D  serial data
  unsigned char     unused3[2];     // 0xFD8E - 0xFD8F  not used
  unsigned char     sdoneack;       // 0xFD90  suzy done acknowledge
  unsigned char     cpusleep;       // 0xFD91  cpu bus request disable
  unsigned char     dispctl;        // 0xFD92  video bus request enable, viddma
  unsigned char     pkbkup;         // 0xFD93  magic 'P' count
  unsigned char     *scrbase;       // 0xFD94  start address of video display
  unsigned char     unused4[6];     // 0xFD96 - 0xFD9B  not used
  unsigned char     mtest0;         // 0xFD9C
  unsigned char     mtest1;         // 0xFD9D
  unsigned char     mtest2;         // 0xFD9E
  unsigned char     unused5;        // 0xFD9F  not used
  unsigned char     palette[32];    // 0xFDA0 - 0xFDBF  palette 32 bytes
                                    // 0xFDC0 - 0xFDFF  not used
};

#ifdef __cplusplus
}
#endif

#endif
