; MEGA65 BASIC header that jumps to _start.

.section .basic_header,"aR",@progbits
#	.short next_line	; address of next BASIC line
        .byte 0x0a, 0x20, 0x0a, 0x00, 0xfe, 0x02, 0x20, 0x30, 0x00 ; 10 BANK 0
        .byte 0x15, 0x20, 0x14, 0x00, 0x9e, 0x20 ; 20 SYS
	.mos_addr_asciz _start, 4	; the location of the _start symbol, in 4 decimal
						; ASCII digits
next_line:
	.short 0   			; end of basic program
