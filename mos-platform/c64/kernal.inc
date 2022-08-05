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
; Olli Savia <ops@iki.fi>
; Greg King
;
; Commodore-compatibles Kernal functions
;

.include "_commodore_kernal.inc"

CINT         = $FF81
IOINIT       = $FF84
RAMTAS       = $FF87

RESTOR       = $FF8A
VECTOR       = $FF8D

SETMSG       = $FF90
SECOND       = $FF93
TKSA         = $FF96
MEMTOP       = $FF99
MEMBOT       = $FF9C
SCNKEY       = $FF9F
SETTMO       = $FFA2
ACPTR        = $FFA5
CIOUT        = $FFA8
UNTLK        = $FFAB
UNLSN        = $FFAE
LISTEN       = $FFB1
TALK         = $FFB4
READST       = $FFB7
SETLFS       = $FFBA
SETNAM       = $FFBD
OPEN         = $FFC0
CLOSE        = $FFC3

LOAD         = $FFD5
SAVE         = $FFD8
SETTIM       = $FFDB
RDTIM        = $FFDE

SCREEN       = $FFED
PLOT         = $FFF0
IOBASE       = $FFF3

; ---------------------------------------------------------------------------
; Kernal routines, direct entries
;
; Unlike the above, these are not standard functions with entries in the jump
; table. They do not exist in all Kernals, and where they do the entry point is
; specific to that particular machine and possibly even Kernal version.
;
; This list is not comprehensive: missing items for particular machines
; should be added as needed.
;
; UPDCRAMPTR: Updates the color RAM pointer to match the screen RAM pointer.
;

CLRSCR       = $E544
KBDREAD      = $E5B4
NMIEXIT      = $FEBC
UPDCRAMPTR   = $EA24
