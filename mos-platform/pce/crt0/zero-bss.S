; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https:;github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

; TODO: This would be best to emit in llvm-mos itself.

.global __do_zero_bss
.section .init.200,"ax",@progbits
__do_zero_bss:
	stz __bss_start
	tii __bss_start, __zero_bss_start, #__zero_bss_size
