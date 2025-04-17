; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.
; Originally from cc65. Modified from original version.

.section .init.010,"ax",@progbits
; Clear decimal mode
        cld

.section .init.050,"ax",@progbits
; Initialization Loop:
; * Clears Atari 2600 whole memory (128 bytes) including BSS segment
; * Clears TIA registers
; * Sets system stack pointer to $ff (i.e top of zero-page)
        ldx     #0
        txa
clearLoop:
        dex
        txs
        pha
        bne     clearLoop

; we jump to main directly here to save 2 bytes of stack
; TODO: how do we get rid of "jsr main" in crt0?
.section .init.400,"ax",@progbits
	jmp	main
