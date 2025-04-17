; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https:;github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.include "imag.inc"

; TODO: This would be best to emit in llvm-mos itself.

.global __do_copy_zp_data
.section .init.200,"ax",@progbits
__do_copy_zp_data:
	tii __zp_data_start, __zp_data_load_start, #__zp_data_size
