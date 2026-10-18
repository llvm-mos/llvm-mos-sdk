; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.zeropage __iodat, __iodir, __viddma, __sprsys
.zeropage _FileCurrBlock, _FileBlockByte, _FileDestPtr

; directory entry
.zeropage _FileStartBlock, _FileBlockOffset, _FileExecFlag, _FileDestAddr, _FileFileLen
