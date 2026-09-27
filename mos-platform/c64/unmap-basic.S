; Switch out the BASIC ROM bank from $A000 to $BFFF.
; This opens up 50KB of contiguous RAM from $0801-$CFFF.
; KERNAL ROM at $E000-$FFFF and I/O at $D000-$DFFF are still mapped.
;
; The ROM must be switched back in before control returns to BASIC - but NOT
; earlier: everything that runs while the program is exiting (exit() and _Exit,
; which are ordinary code and may be linked at $A000 or above in a large
; program, and the data they use) needs the RAM view. Switching it back in a
; .fini section, before exit() had finished, made exit() return into BASIC ROM.
;
; So the restore is tied to the actual return to BASIC. That return is an RTS
; to the address BASIC's SYS left on the hardware stack (save-basic.o's _Exit
; resets the stack pointer and executes it). At startup that address is
; replaced by __c64_return_to_basic, a small routine in low memory (it sits in
; the init section, which is linked at the start of the program) that switches
; the ROM back in and then returns to BASIC's address. A program that never
; returns to BASIC (the default _Exit loops forever) never uses it and simply
; keeps the RAM view.

; Saved before the .bss is zeroed (.init.200), so it must not live in .bss.
.section .noinit,"aw",@nobits
__basic_ret:
        .fill 2

; bank switching needs to complete before any CRT initialization
.section .init.010,"ax",@progbits
        ldx #$2F ; restore default CPU I/O port data directions
        stx 0    ;
        ldx #$3E ; LORAM = 0
        stx 1    ; switch out BASIC ROM at $A000-$BFFF for RAM

        tsx
        cpx #$FE                 ; no return address on the stack (S=$FE/$FF):
        bcs .Lskip               ; nothing to divert
        lda $0101,x              ; BASIC's return address, as pushed (low, high)
        sta __basic_ret
        lda $0102,x
        sta __basic_ret+1
        lda #mos16lo(__c64_return_to_basic-1)
        sta $0101,x
        lda #mos16hi(__c64_return_to_basic-1)
        sta $0102,x
        jmp .Lskip

        ; Entered by the RTS that returns to BASIC. Everything it reads is read
        ; while the RAM view is still active; the instruction after the write
        ; to the CPU port is fetched from this low, always-RAM code.
.global __c64_return_to_basic
__c64_return_to_basic:
        lda __basic_ret+1
        pha
        lda __basic_ret
        pha
        ldx #$3F ; LORAM = 1
        stx 1    ; switch in BASIC ROM at $A000-$BFFF
        rts
.Lskip:
