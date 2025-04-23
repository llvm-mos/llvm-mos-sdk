; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 16.05.2000
;
; extern unsigned char __oserror;
; /* Operating system specific errors from the low level functions */


        .globl         __oserror

.bss

__oserror:
        .fill    1
