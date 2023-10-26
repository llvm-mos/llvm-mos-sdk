; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 19.11.2002
;
; C128 Kernal functions
;

#define __C128__ 1
#include <cbm_kernal.inc>

.macro weakdef name:req
  .weak \name
  __\name = \name
  .global __\name
.endm

weakdef KBDREAD
weakdef CLRSCR
weakdef PRINT
weakdef NEWLINE
weakdef CURS_SET
weakdef CURS_ON
weakdef CURS_OFF
weakdef NMIEXIT

weakdef C64MODE
weakdef SWAPPER
weakdef SETBNK

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
weakdef PLOT
weakdef IOBASE
