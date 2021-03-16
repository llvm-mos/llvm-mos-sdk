; Many 8-bit home computers use this format for a BASIC header to their
; programs.  This structures that BASIC header in such a way that other programs
; can change it.

.section .text.basic_header
	.short next_line
	             ; address of next BASIC line
	.short 7773  ; line number: l33t for LLVM, a hint that this program was
	             ; compiled with LLVM
	; The SYS keyword and the usually ASCII string representing the jump target
	basic_sys_command
next_line:
	.short 0    ; end of basic program
