; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 19.11.2002
;
; C64 Kernal functions
;

#define __C64__ 1
#include <cbm_kernal.inc>

.macro weakdef name:req
  .weak \name
  __\name = \name
  .global __\name
.endm

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

weakdef KTEMP2
weakdef FNAM
weakdef TXTPTR

weakdef BASIC_BUF
weakdef SCREEN_PTR
weakdef STATUS
weakdef IN_DEV
weakdef OUT_DEV
weakdef FNAM_LEN
weakdef SECADR
weakdef DEVADR

weakdef CINV
weakdef CBINV
weakdef NMINV
weakdef IOPEN
weakdef ICLOSE
weakdef ICHKIN
weakdef ICKOUT
weakdef ICLRCH
weakdef IBASIN
weakdef IBSOUT
weakdef ISTOP
weakdef IGETIN
weakdef ICLALL
weakdef ILOAD
weakdef ISAVE

weakdef CURS_COLOR
weakdef CHARCOLOR
weakdef RVS
weakdef CURS_FLAG
weakdef CURS_BLINK
weakdef CURS_CHAR
weakdef CURS_STATE
weakdef CURS_X
weakdef CURS_Y
weakdef LLEN
weakdef NLINES
weakdef VARTAB
weakdef MEMSIZ