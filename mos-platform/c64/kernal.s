; Copyright 2022 LLVM-MOS Project
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 19.11.2002
;
; C64 Kernal functions
;

.include "kernal.inc"

.macro weakdef name:req
  .weak \name
  __\name = \name
  .global __\name
.endm

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

weakdef LOAD
weakdef SAVE
weakdef SETTIM
weakdef RDTIM

weakdef SCREEN
weakdef PLOT
weakdef IOBASE

weakdef CLRSCR
weakdef KBDREAD
weakdef NMIEXIT
weakdef UPDCRAMPTR
