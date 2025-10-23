.include "rp6502.inc"

; The errno on the RP6502 RIA is the errno for llvm-mos.
; There is no oserror and nothing calls __mappederrno.

.global _errno
.set _errno, RIA_ERRNO

; Request the RIA use llvm-mos values for RIA_ERRNO

.section .init.100,"ax",@progbits
  lda #$02 ; 2 = llvm-mos
  sta RIA_A
  lda #RIA_OP_ERRNO_OPT
  sta RIA_OP
  jsr RIA_SPIN
