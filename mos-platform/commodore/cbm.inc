; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Include file for the Commdore 6502 machines
;

;-----------------------------------------------------------------------------
; Device numbers
;

CBMDEV_KBD      = 0
CBMDEV_DATASETTE= 1
CBMDEV_RS232    = 2
CBMDEV_SCREEN   = 3

;-----------------------------------------------------------------------------
; Disk stuff
;

MAX_DRIVES      = 23
FIRST_DRIVE     = 8
