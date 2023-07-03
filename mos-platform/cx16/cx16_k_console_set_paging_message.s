.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_set_paging_message(void *msgaddr);
; llvm-mos:                                    rc2/3
; llvm-mos aliases:                            r0
; X16 kernal:                                  r0
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_set_paging_message
;
.global cx16_k_console_set_paging_message
cx16_k_console_set_paging_message:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
    					; r0 = addr (already set)
	jsr	__CONSOLE_SET_PAGE_MSG
	X16_kernal_pop_r6_r10
	rts
