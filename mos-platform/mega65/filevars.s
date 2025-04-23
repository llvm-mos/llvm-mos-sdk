; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 15.11.2002
;
; Variables used for Mega65 file I/O
;

        .globl         curunit


.bss
curunit:
        .fill    1


.section .init,"ax",@progbits
initcurunit:
        lda     #8              ; Default is disk
        sta     curunit
