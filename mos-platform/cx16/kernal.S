; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.
;
; Originally from cc65. Modified from original version.
;
; Ullrich von Bassewitz, 19.11.2002
;
; Commander X16 Kernal functions
;

#define __CX16__ 1
#include <cbm_kernal.inc>

.macro weakdef name:req
  .weak \name
  __\name = \name
  .global __\name
.endm

weakdef BSAVE
weakdef KBDBUF_PEEK
weakdef KBDBUF_GET_MODIFIERS
weakdef KBDBUF_PUT
weakdef I2C_READ_BYTE
weakdef I2C_WRITE_BYTE
weakdef CX_MONITOR
weakdef ENTROPY_GET
weakdef KEYMAP
weakdef CONSOLE_SET_PAGE_MSG
weakdef CONSOLE_PUT_IMAGE
weakdef CONSOLE_INIT
weakdef CONSOLE_PUT_CHAR
weakdef CONSOLE_GET_CHAR
weakdef MEMORY_FILL
weakdef MEMORY_COPY
weakdef MEMORY_CRC
weakdef MEMORY_DECOMPRESS
weakdef SPRITE_SET_IMAGE
weakdef SPRITE_SET_POSITION
weakdef FB_INIT
weakdef FB_GET_INFO
weakdef FB_SET_PALETTE
weakdef FB_CURSOR_POSITION
weakdef FB_CURSOR_NEXT_LINE
weakdef FB_GET_PIXEL
weakdef FB_GET_PIXELS
weakdef FB_SET_PIXEL
weakdef FB_SET_PIXELS
weakdef FB_SET_8_PIXELS
weakdef FB_SET_8_PIXELS_OPAQUE
weakdef FB_FILL_PIXELS
weakdef FB_FILTER_PIXELS
weakdef FB_MOVE_PIXELS
weakdef GRAPH_INIT
weakdef GRAPH_CLEAR
weakdef GRAPH_SET_WINDOW
weakdef GRAPH_SET_COLORS
weakdef GRAPH_DRAW_LINE
weakdef GRAPH_DRAW_RECT
weakdef GRAPH_MOVE_RECT
weakdef GRAPH_DRAW_OVAL
weakdef GRAPH_DRAW_IMAGE
weakdef GRAPH_SET_FONT
weakdef GRAPH_GET_CHAR_SIZE
weakdef GRAPH_PUT_CHAR
weakdef MACPTR
weakdef ENTER_BASIC
weakdef CLOCK_SET_DATE_TIME
weakdef CLOCK_GET_DATE_TIME
weakdef JOYSTICK_SCAN
weakdef JOYSTICK_GET
weakdef SCREEN_MODE
weakdef SCREEN_SET_CHARSET
weakdef MOUSE_CONFIG
weakdef MOUSE_GET
weakdef MOUSE_SCAN

weakdef CHKIN
weakdef CKOUT
weakdef CHKOUT
weakdef CLRCH
weakdef CLRCHN
weakdef BASIN
weakdef CHRIN
weakdef BSOUT
weakdef CHROUT
weakdef STOP
weakdef GETIN
weakdef CLALL
weakdef UDTIM

weakdef CLRSCR
weakdef KBDREAD
weakdef UPDCRAMPTR
weakdef NMIEXIT

weakdef CINT
weakdef IOINIT
weakdef RAMTAS
weakdef RESTOR
weakdef VECTOR
weakdef SETMSG
weakdef SECOND
weakdef TKSA
weakdef MEMTOP
weakdef MEMBOT
weakdef SCNKEY
weakdef SETTMO
weakdef ACPTR
weakdef CIOUT
weakdef UNTLK
weakdef UNLSN
weakdef LISTEN
weakdef TALK
weakdef READST
weakdef SETLFS
weakdef SETNAM
weakdef OPEN
weakdef CLOSE
weakdef CHKIN
weakdef CKOUT
weakdef CLRCH
weakdef BASIN
weakdef CHRIN
weakdef BSOUT
weakdef CHROUT
weakdef LOAD
weakdef SAVE
weakdef SETTIM
weakdef RDTIM
weakdef STOP
weakdef GETIN
weakdef CLALL
weakdef UDTIM
weakdef SCREEN
weakdef IOBASE
