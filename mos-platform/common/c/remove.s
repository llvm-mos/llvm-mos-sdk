; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 2003-08-12
;
; int __fastcall__ remove (const char* name);
;

        .globl         remove

;--------------------------------------------------------------------------

remove:

        jsr     __sysremove     ; Call the machine specific function
        jmp     __mappederrno   ; Store into __oserror, set errno, return 0/-1
