/********************************************************************
 * SamVlir.h
 *
 * This file contains global definitions for the llvm-mos GEOS VLIR
 * sample application.
 *
 ********************************************************************/

#ifndef SAMVLIR_H
#define SAMVLIR_H

#define NUM_MODS 2 /* This application has 2 swap modules */
#define MOD_FILE 1 /* record number for file module */
#define MOD_EDIT 2 /* record number for edit module */

#define NUM_DA 7 /* Geos menu can list names of 7 desk accessories*/

/* Defines for main menu */

#define MM_COUNT 3   /* Number of main menu items */
#define MM_TOP 0     /* top scanline of menu */
#define MM_BOTTOM 14 /* bottom scanline of menu */
#define MM_LEFT 0    /* left pixel position of menu */
#define MM_RIGHT 72  /* right pixel position of menu */

/* top of all submenus */
#define SM_TOP (MM_BOTTOM + 1)

/* defines for GEOS menu */
#define GM_COUNT                                                               \
  1                 /* no of items (assuming no desk accessories               \
                       InitDA will adjust table) */
#define GM_LEFT 0   /* left x position */
#define GM_WIDTH 79 /* width in pixels */

/* defines for FILE menu */

#define FM_COUNT 2  /* number of items */
#define FM_LEFT 29  /* left x position */
#define FM_WIDTH 40 /* width in pixels */

/* defines for EDIT menu */

#define EM_COUNT 3  /* number of items */
#define EM_LEFT 49  /* left x position */
#define EM_WIDTH 40 /* width in pixels */

/* resident module exports */
extern char DAText[8][17];

/* File module exports */
extern __attribute__((noinline)) void RunDA(uint8_t da_index);
extern __attribute__((noinline)) void DoClose(void);

/* Edit module exports */
extern __attribute__((noinline)) void DoCut(void);
extern __attribute__((noinline)) void DoCopy(void);
extern __attribute__((noinline)) void DoPaste(void);
extern __attribute__((noinline)) void DoIcon1(void);

/* Import from linker definition file overlay start and size */
extern uint8_t __overlayaddr;
extern uint8_t __overlaysize;
#define OVERLAYADDR ((uint8_t *)&__overlayaddr)
#define OVERLAYSIZE ((uint16_t)&__overlaysize)

#endif
