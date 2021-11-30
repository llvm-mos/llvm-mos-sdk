; C64 BASIC header that jumps to _start = 2061. This address immediately
; follows the header if it's at the beginning of BASIC memory ($0801).

.section .basic_header,"aR",@progbits
	.short next_line	; address of next BASIC line
	.short 7773 		; line number: l33t for LLVM, a hint that this program was
						; compiled with LLVM
	.byte 0x9e			; SYS keyword BASIC token
	.asciz "2061"		; the location of the _start symbol, in ASCII
next_line:
	.short 0   			; end of basic program
