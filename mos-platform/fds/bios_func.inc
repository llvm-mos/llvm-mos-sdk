.macro addpointer i=0
  .Larg\i:
    .word $ADDE
.endm

.macro loadstore i=0
  ldy __rc2 + [\i * 2]
  sty .Larg\i
  ldy __rc3 + [\i * 2]
  sty .Larg\i + 1
.endm

; Some BIOS functions require pointers to be provided by specifying them
; right after the function call, inline with the rest of the routine.
; This means that pointers are typically provided statically;
; to make these functions dynamic and give them a more familiar C interface,
; we modify the pointer arguments during runtime.
.altmacro
.macro pointerfunc sym:req, args=1
  .set i,0
  .rept \args
    loadstore %i
    .set i,i+1
  .endr
  jsr \sym
  .set i,0
  .rept \args
    addpointer %i
    .set i,i+1
  .endr
.endm
