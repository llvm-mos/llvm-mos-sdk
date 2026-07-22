; callmain.s
; Load __argc and __argv into the llvm-mos argument registers before
; the common crt0's "jsr main". This fragment is placed in .call_main
; and lands before common/crt0/crt0.S because rp6502-crt0-o is merged
; before common-crt0-o in the archive.
;
; int main(int argc, char **argv) calling convention:
;   argc (int)    -> A (lo byte), X (hi byte)
;   argv (char**) -> __rc2 (lo byte), __rc3 (hi byte)

.include "imag.inc"

.section .call_main,"ax",@progbits
  ; argv -> __rc2:__rc3
  lda __argv
  sta __rc2
  lda __argv+1
  sta __rc3
  ; argc -> A:X
  ldx __argc+1
  lda __argc
  ; falls through to "jsr main" in common/crt0/crt0.S
