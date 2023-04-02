; Copyright 2022 LLVM-MOS Project                                                                        
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
; information.                                                                                           

; Originally from cc65. Modified from original version.                                                  

;                                                                                                        
; Ullrich von Bassewitz, 19.11.2002                                                                      
;                                                                                                        
; PET Kernal functions                                                                                   
;                                                                                                        

#define __PET__ 1
#include <cbm_kernal.inc>

.macro weakdef name:req
  .weak \name
  __\name = \name
  .global __\name
.endm

weakdef CLRCH
weakdef BASIN
weakdef CHRIN
weakdef STOP
weakdef GETIN
weakdef CLALL
weakdef UDTIM
weakdef CHROUT
weakdef BSOUT
weakdef CHRIN
