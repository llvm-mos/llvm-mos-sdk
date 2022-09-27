.macro cpmentry sym:req, num:req, exiter=__exit
	.section .text.\sym, "ax", @progbits
	.global \sym
\sym:
	ldy #\num
	jsr BDOS
	jmp \exiter
.endm

.macro cpmentry_p sym:req, num:req, exiter=__exit
	.section .text.\sym, "ax", @progbits
	.global \sym
\sym:
	lda __rc2
	ldx __rc3
	ldy #\num
	jsr BDOS
	jmp \exiter
.endm

cpmentry   cpm_warmboot,               0
cpmentry   cpm_conin,                  1, __cpmexiter_byte
cpmentry   cpm_conout,                 2
cpmentry   cpm_auxin,                  3, __cpmexiter_byte
cpmentry   cpm_auxout,                 4
cpmentry   cpm_lstout,                 5
cpmentry   cpm_conio,                  6, __cpmexiter_byte
cpmentry   cpm_get_iobyte,             7, __cpmexiter_byte
cpmentry   cpm_set_iobyte,             8
cpmentry_p cpm_printstring,            9
cpmentry_p cpm_readline,              10, __cpmexiter_byte
cpmentry   cpm_const,                 11, __cpmexiter_byte
cpmentry   cpm_get_version,           12
cpmentry   cpm_reset_disk_system,     13
cpmentry   cpm_select_drive,          14
cpmentry_p cpm_open_file,             15, __cpmexiter_byte
cpmentry_p cpm_close_file,            16, __cpmexiter_byte
cpmentry_p cpm_findfirst,             17, __cpmexiter_byte
cpmentry_p cpm_findnext,              18, __cpmexiter_byte
cpmentry_p cpm_delete_file,           19, __cpmexiter_byte
cpmentry_p cpm_read_sequential,       20, __cpmexiter_byte
cpmentry_p cpm_write_sequential,      21, __cpmexiter_byte
cpmentry_p cpm_make_file,             22, __cpmexiter_byte
cpmentry_p cpm_rename_file,           23, __cpmexiter_byte
cpmentry   cpm_get_login_vector,      24
cpmentry   cpm_get_current_drive,     25, __cpmexiter_byte
cpmentry_p cpm_set_dma,               26
cpmentry   cpm_get_allocation_vector, 27, __cpmexiter_ptr
cpmentry   cpm_write_protect_drive,   28
cpmentry   cpm_get_readonly_vector,   29
cpmentry_p cpm_set_file_attributes,   30, __cpmexiter_byte
cpmentry   cpm_get_dpb,               31, __cpmexiter_ptr
cpmentry   cpm_get_set_user,          32, __cpmexiter_byte
cpmentry_p cpm_read_random,           33, __cpmexiter_byte
cpmentry_p cpm_write_random,          34, __cpmexiter_byte
cpmentry_p cpm_seek_to_end,           35
cpmentry_p cpm_seek_to_seq_pos,       36
cpmentry   cpm_reset_drives,          37, __cpmexiter_byte
cpmentry_p cpm_write_random_filled,   40, __cpmexiter_byte

.section .text.cpmexit_byte, "ax", @progbits
	; On exit from the BDOS (or BIOS), the return value is in A
	; and carry is set on error.

__cpmexiter_byte:
	ldx #0
	bcc __exit

	; Negate A.

	eor #$ff
	sec
	adc #0

	dex
__exit:
	rts

.section .text.cpmexit_ptr, "ax", @progbits
__cpmexiter_ptr:
	sta __rc2
	stx __rc3
	rts

