; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Christian Groessler, Oct-2000
; Daniel Serpell, Dec-2009
;
; the fdtable itself is defined here
;

        .include "fd.inc"

        .globl fd_table,fd_index

        .data

fd_index:       ; fd number is index into this table, entry's value specifies the fd_table entry
        .byte   0,0,0           ; at start, three first files are stdin/stdout/stderr.
        .space  MAX_FD_INDEX-3,$ff

fd_table:       ; each entry represents an open iocb
        .byte   3,0,'E',0       ; system console, app starts with opened iocb #0 for E:
        .byte   0,$ff,0,0
        .byte   0,$ff,0,0
        .byte   0,$ff,0,0
        .byte   0,$ff,0,0
        .byte   0,$ff,0,0
        .byte   0,$ff,0,0
        .byte   0,$ff,0,0

