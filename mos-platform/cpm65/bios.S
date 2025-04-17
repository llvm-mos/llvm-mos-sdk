; Sets up the BIOS entrypoint.
;
; © 2022 David Given
; This file is part of the llvm-mos-sdk project and is redistributable under the
; terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE file
; in the project root for the full text.

.section .init.200, "ax", @progbits
__do_setup_bios:
	ldy #38
	jsr BDOS
	sta BIOS+1
	stx BIOS+2

.text

.global BIOS
BIOS:
	jmp 0 ; patched by startup code

