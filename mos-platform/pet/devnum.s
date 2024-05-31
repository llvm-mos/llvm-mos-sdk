; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Oliver Schmidt, 2010-02-14
;

        .include        "pet.inc"

        .globl       devnum
        .zeropage    devnum

devnum = DEVNUM
