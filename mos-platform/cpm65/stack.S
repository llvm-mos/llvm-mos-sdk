; C stack definition.
;
; © 2022 David Given
; This file is part of the llvm-mos-sdk project and is redistributable under the
; terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE file
; in the project root for the full text.

.global __stack

; This goes in the noinit area rather than being at the top of program
; workspace because llvm-mos doesn't know whether the program wants to
; overwrite the CCP or not.

.section .noinit, "wa", @nobits
stack_start:
	.fill 2*1024
__stack:

