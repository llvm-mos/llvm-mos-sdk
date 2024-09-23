/***********************************************************************
 * geos_memorymap.h
 *
 * This file contains symbol definitions for use in GEOS applications
 * with llvm-mos C compiler.
 *
 * Transcribed from geoProgrammer manual by DiSc.
 *
 ***********************************************************************/

#ifndef GEOS_MEMORYMAP_H
#define GEOS_MEMORYMAP_H

#define APP_RAM 0x0400       /** start of application space */
#define BACK_SCR_BASE 0x6000 /** base of background screen */
#define PRINTBASE 0x7900     /** load address for print drivers */
#define APP_VAR 0x7f40       /** application variable space */
#define OS_VARS 0x8000       /** OS variable base */
#define SPRITE_PICS 0x8a00   /** base of sprite pictures */
#define COLOR_MATRIX 0x8c00  /** video color matrix */
#define DISK_BASE 0x9000     /** disk driver base address */
#define SCREEN_BASE 0xa000   /** base of foreground screen */
#define OS_ROM 0xc000        /** start of OS code space */
#define OS_JUMPTAB 0xc100    /** start of GEOS jump table */
#define EXP_BASE 0xdf00      /** base address of ram expansion unit */
#define MOUSE_BASE_128 0xfd00
#define MOUSE_JMP_128 0xfd00
#define MOUSE_JMP 0xfe80  /** start of mouse jump table */
#define MOUSE_BASE 0xfe80 /** start of input driver */
#define END_MOUSE_128 0xfe80
#define config 0xff00
#define END_MOUSE 0xfffa /** end of input driver */

#endif