; Imaginary register definitions.
;
; © 2022 David Given
; This file is part of the llvm-mos-sdk project and is redistributable under the
; terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE file
; in the project root for the full text.

; We define registers as variables each in their own section, rather than
; statically in the linker script, to allow the linker to discard them if
; they're not in use. The compiler doesn't always use them all and
; hand-written machine code only rarely uses any.

.macro register n, m
	.section .zp.reg_\n\()_\m, "zaw", @nobits
		.global __rc\n, __rc\m
		__rc\n: .fill 1
		__rc\m: .fill 1
.endm

register 0, 1
register 2, 3
register 4, 5
register 6, 7
register 8, 9
register 10, 11
register 12, 13
register 14, 15
register 16, 17
register 18, 19
register 20, 21
register 22, 23
register 24, 25
register 26, 27
register 28, 29
register 30, 31

