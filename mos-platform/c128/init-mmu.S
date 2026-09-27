.include "c128.inc"

; A C program runs with $4000-$BFFF mapped to RAM (MMU_CFG_RAM0_KERNAL); BASIC
; runs with ROM there. The original configuration must be put back before
; control returns to BASIC - but NOT earlier: everything that runs while the
; program is exiting (exit() and _Exit, which are ordinary code and may be
; linked above $4000 in a large program, and the data they use) needs the RAM
; view. Restoring in a .fini section, before exit() had finished, made
; exit() return into BASIC ROM.
;
; So the restore is tied to the actual return to BASIC. That return is an RTS
; to the address BASIC's SYS left on the hardware stack (save-basic.o's _Exit
; resets the stack pointer and executes it). At startup that address is
; replaced by __c128_return_to_basic, a small routine in low memory (it sits
; in the init section, which is linked at the start of the program) that
; restores the configuration and then returns to BASIC's address. A program
; that never returns to BASIC (the default _Exit loops forever) never uses it
; and simply keeps the RAM view.

; The startup values are saved before the .bss is zeroed (.init.200), so they
; must not live in .bss.
.section .noinit,"aw",@nobits
__mmusave:
  .fill 1
__basic_ret:
  .fill 2

; MMU initialization needs to complete before any CRT initialization
.section .init.010,"ax",@progbits
        lda MMU_CR
        sta __mmusave
        lda #MMU_CFG_RAM0_KERNAL ; map $4000-$BFFF to RAM, $C000-$FFFF to KERNAL/chargen
        sta MMU_CR

        tsx
        cpx #$FE                 ; no return address on the stack (S=$FE/$FF):
        bcs .Lskip               ; nothing to divert
        lda $0101,x              ; BASIC's return address, as pushed (low, high)
        sta __basic_ret
        lda $0102,x
        sta __basic_ret+1
        lda #mos16lo(__c128_return_to_basic-1)
        sta $0101,x
        lda #mos16hi(__c128_return_to_basic-1)
        sta $0102,x
        jmp .Lskip

        ; Entered by the RTS that returns to BASIC. Everything it reads is read
        ; while the RAM view is still active; the instruction after the write
        ; to MMU_CR is fetched from this low, always-RAM code.
.global __c128_return_to_basic
__c128_return_to_basic:
        lda __basic_ret+1
        pha
        lda __basic_ret
        pha
        lda __mmusave
        sta MMU_CR
        rts
.Lskip:
