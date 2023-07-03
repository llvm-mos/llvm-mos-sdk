; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.global pce_bank23i_set
.global pce_bank2_size2i_set
.global pce_bank234i_set
.global pce_bank2_size3i_set
.global pce_bank2345i_set
.global pce_bank2_size4i_set
.global pce_bank23456i_set
.global pce_bank2_size5i_set
.global pce_bank34i_set
.global pce_bank3_size2i_set
.global pce_bank345i_set
.global pce_bank3_size3i_set
.global pce_bank3456i_set
.global pce_bank3_size4i_set
.global pce_bank45i_set
.global pce_bank4_size2i_set
.global pce_bank456i_set
.global pce_bank4_size3i_set
.global pce_bank56i_set
.global pce_bank5_size2i_set

    .section .text.bank23i, "ax", @progbits
pce_bank23i_set:
pce_bank2_size2i_set:
    tam #$04
    inc
    tam #$08
    rts

    .section .text.bank234i, "ax", @progbits
pce_bank234i_set:
pce_bank2_size3i_set:
    tam #$04
    inc
pce_bank34i_set:
pce_bank3_size2i_set:
    tam #$08
    inc
    tam #$10
    rts

    .section .text.bank2345i, "ax", @progbits
pce_bank2345i_set:
pce_bank2_size4i_set:
    tam #$04
    inc
pce_bank345i_set:
pce_bank3_size3i_set:
    tam #$08
    inc
pce_bank45i_set:
pce_bank4_size2i_set:
    tam #$10
    inc
    tam #$20
    rts

    .section .text.bank23456i, "ax", @progbits
pce_bank23456i_set:
pce_bank2_size5i_set:
    tam #$04
    inc
pce_bank3456i_set:
pce_bank3_size4i_set:
    tam #$08
    inc
pce_bank456i_set:
pce_bank4_size3i_set:
    tam #$10
    inc
pce_bank56i_set:
pce_bank5_size2i_set:
    tam #$20
    inc
    tam #$40
    rts
