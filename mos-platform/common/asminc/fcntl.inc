; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65.

;
; Ullrich von Bassewitz, 05.06.1999
;

; Predefined file handles
STDIN_FILENO    = 0
STDOUT_FILENO   = 1
STDERR_FILENO   = 2

; File mode constants, must match the values in the C headers
O_RDONLY        = $01
O_WRONLY        = $02
O_RDWR          = $03
O_CREAT         = $10
O_TRUNC         = $20
O_APPEND        = $40
O_EXCL          = $80
