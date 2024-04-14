; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 16.11.2002
;
; unsigned char __fastcall__ _sysremove (const char* name);
;

        .globl         __sysremove

;--------------------------------------------------------------------------
; __sysremove:

__sysremove:

        jsr     fnparse         ; Parse the given file name
        bne     err             ; Jump if yes
        jmp     scratch         ; Scratch the file, return an error code
err:    rts
