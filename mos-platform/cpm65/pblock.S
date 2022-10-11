; Parameter passing block for CP/M-65. This is immediately after the program
; text (and just before the BSS) and is filled out by the CCP when programs are
; loaded.
;
; This file is part of the llvm-mos-sdk project and is redistributable under
; the terms of the Apache 2.0 license. See the LICENSE file in the project root
; for the full text.

.global cpm_fcb
.global cpm_fcb2
.global cpm_default_dma
.global cpm_cmdlinelen
.global cpm_cmdline

.section .pblock, "wa", @nobits
cpm_fcb:	     .fill 37
cpm_fcb2 = cpm_fcb + 16
cpm_default_dma:
cpm_cmdlinelen:  .fill 1
cpm_cmdline:	 .fill 127
