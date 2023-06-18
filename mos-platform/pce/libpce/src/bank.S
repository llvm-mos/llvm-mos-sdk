; Copyright (c) 2023 Adrian "asie" Siekierka
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.

.global pce_bank2_set
.global pce_bank2i_set
.global pce_bank2_size1_set
.global pce_bank2_size1i_set
.global pce_bank23_set
.global pce_bank23i_set
.global pce_bank2_size2_set
.global pce_bank2_size2i_set
.global pce_bank234_set
.global pce_bank234i_set
.global pce_bank2_size3_set
.global pce_bank2_size3i_set
.global pce_bank2345_set
.global pce_bank2345i_set
.global pce_bank2_size4_set
.global pce_bank2_size4i_set
.global pce_bank23456_set
.global pce_bank23456i_set
.global pce_bank2_size5_set
.global pce_bank2_size5i_set
.global pce_bank3_set
.global pce_bank3i_set
.global pce_bank3_size1_set
.global pce_bank3_size1i_set
.global pce_bank34_set
.global pce_bank34i_set
.global pce_bank3_size2_set
.global pce_bank3_size2i_set
.global pce_bank345_set
.global pce_bank345i_set
.global pce_bank3_size3_set
.global pce_bank3_size3i_set
.global pce_bank3456_set
.global pce_bank3456i_set
.global pce_bank3_size4_set
.global pce_bank3_size4i_set
.global pce_bank4_set
.global pce_bank4i_set
.global pce_bank4_size1_set
.global pce_bank4_size1i_set
.global pce_bank45_set
.global pce_bank45i_set
.global pce_bank4_size2_set
.global pce_bank4_size2i_set
.global pce_bank456_set
.global pce_bank456i_set
.global pce_bank4_size3_set
.global pce_bank4_size3i_set
.global pce_bank5_set
.global pce_bank5i_set
.global pce_bank5_size1_set
.global pce_bank5_size1i_set
.global pce_bank56_set
.global pce_bank56i_set
.global pce_bank5_size2_set
.global pce_bank5_size2i_set
.global pce_bank6_set
.global pce_bank6i_set
.global pce_bank6_size1_set
.global pce_bank6_size1i_set

    .section .text.bank23, "ax", @progbits
pce_bank23_set:
pce_bank2_size2_set:
    tam #$04
pce_bank3_set:
pce_bank3_size1_set:
    tam #$08
    rts

    .section .text.bank23i, "ax", @progbits
pce_bank23i_set:
pce_bank2_size2i_set:
    tam #$04
    inc
pce_bank3i_set:
pce_bank3_size1i_set:
    tam #$08
    rts

    .section .text.bank234, "ax", @progbits
pce_bank234_set:
pce_bank2_size3_set:
    tam #$04
pce_bank34_set:
pce_bank3_size2_set:
    tam #$08
pce_bank4_set:
pce_bank4_size1_set:
    tam #$10
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
pce_bank4i_set:
pce_bank4_size1i_set:
    tam #$10
    rts

    .section .text.bank2345, "ax", @progbits
pce_bank2345_set:
pce_bank2_size4_set:
    tam #$04
pce_bank345_set:
pce_bank3_size3_set:
    tam #$08
pce_bank45_set:
pce_bank4_size2_set:
    tam #$10
pce_bank5_set:
pce_bank5_size1_set:
    tam #$20
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
pce_bank5i_set:
pce_bank5_size1i_set:
    tam #$20
    rts

    .section .text.bank23456, "ax", @progbits
pce_bank23456_set:
pce_bank2_size5_set:
    tam #$04
pce_bank3456_set:
pce_bank3_size4_set:
    tam #$08
pce_bank456_set:
pce_bank4_size3_set:
    tam #$10
pce_bank56_set:
pce_bank5_size2_set:
    tam #$20
pce_bank6_set:
pce_bank6_size1_set:
    tam #$40
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
pce_bank6i_set:
pce_bank6_size1i_set:
    tam #$40
    rts