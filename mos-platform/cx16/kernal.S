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
