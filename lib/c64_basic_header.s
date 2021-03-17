; SYS 2061 in C64 BASIC
.macro basic_sys_command
	.byte 0x9e   ; SYS keyword BASIC token
	.asciz "2061" ; the location of the _start symbol, in ASCII
.endm

.include "lib/basic_header.s"

