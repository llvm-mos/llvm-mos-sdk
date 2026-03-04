; Save/restore BASIC zero page state for clean return to BASIC interpreter.
; Link with -l:save-basic.o to enable; overrides the default infinite-loop _Exit.
;
; Uses linker symbols __basic_zp_start and __basic_zp_size (computed in
; commodore.ld from per-target __basic_zp_start/__basic_zp_end), so each
; Commodore platform automatically saves its correct ZP range.

; --- Save ZP + hardware stack pointer (before ROM unmap at .init.010) ---
.section .init.005, "ax", @progbits
  ; Save hardware stack pointer for _Exit to restore on return to BASIC.
  tsx
  stx __saved_basic_s

  ; Save BASIC zero page (__basic_zp_start to __basic_zp_end - 1).
  ldx #0
.Lsave_zp:
  lda __basic_zp_start,x
  sta __saved_basic_zp,x
  inx
  cpx #mos16lo(__basic_zp_size)
  bne .Lsave_zp

; --- Restore ZP (before ROM restore and cli at .fini.990) ---
.section .fini.989, "ax", @progbits
  ldx #0
.Lrestore_zp:
  lda __saved_basic_zp,x
  sta __basic_zp_start,x
  inx
  cpx #mos16lo(__basic_zp_size)
  bne .Lrestore_zp

; --- Override weak _Exit: restore hardware S and return to BASIC ---
; Skips finalization (_fini) by design, matching C semantics for _Exit.
; The normal exit() path runs _fini first (restoring ZP and ROMs), then
; calls _Exit which only needs to restore the hardware stack pointer.
.globl _Exit
.section .text._Exit, "ax", @progbits
_Exit:
  ldx __saved_basic_s
  txs
  rts

; --- Buffer in .noinit (no PRG file size cost) ---
.section .noinit, "aw", @nobits
__saved_basic_zp:
  .fill 144               ; max ZP size across Commodore targets (VIC-20: $00-$8F)
__saved_basic_s:
  .fill 1
