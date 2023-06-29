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
    					; r0 = addr (already set)
	jmp	__CONSOLE_SET_PAGE_MSG
