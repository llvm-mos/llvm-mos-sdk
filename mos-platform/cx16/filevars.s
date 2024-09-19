; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

; 2002-11-15, Ullrich von Bassewitz
; 2019-11-08, Greg King
;
; Variables used for CBM file I/O
;

        .globl         curunit

        .include        "cx16.inc"


.bss
curunit:
        .fill    1


.section .init,"ax",@progbits
initcurunit:
        lda     DEVNUM
        bne     L0
        lda     #8              ; Default is SD card
        sta     DEVNUM
L0:     sta     curunit


.section .fini,"ax",@progbits
updatedevnum:
        lda     curunit
        sta     DEVNUM
