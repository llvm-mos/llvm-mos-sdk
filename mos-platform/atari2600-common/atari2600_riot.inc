; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.
; Originally from cc65.

; Atari 2600 RIOT read / write registers
;
; Source: DASM - vcs.h
; Details available in: Stella Programmer's Guide by Steve Wright
;
; Florent Flament (contact@florentflament.com), 2017

; Read registers
SWCHA  = $0280
SWACNT = $0281
SWCHB  = $0282
SWBCNT = $0283
INTIM  = $0284
TIMINT = $0285

; Write registers
TIM1T  = $0294
TIM8T  = $0295
TIM64T = $0296
T1024T = $0297
