; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.include "lynx.inc"
.include "imag.inc"

; ------------------------------------------------------------------------
; READ: Read a particular joystick passed in A.

.global lynx_joy_read
lynx_joy_read:
        lda     SWITCHES
        and     #$01
        tax
        lda     JOYSTICK
        rts
