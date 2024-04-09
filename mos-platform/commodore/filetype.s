; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 2012-07-15
;
; Default file type used when creating new files
;

        .globl         __filetype


.data

__filetype:
        .byte   'S'             ; Create sequential files by default
