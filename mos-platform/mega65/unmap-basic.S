; Switch out the BASIC ROM bank from $A000 to $BFFF.
; This opens up 45KB of contiguous RAM from $2001-$CFFF.
; KERNAL ROM at $E000-$FFFF and I/O at $D000-$DFFF are still mapped.



; bank switching needs to complete before any CRT initialization
.section .init.010,"ax",@progbits
	sei
        ldx #$2F ; restore default CPU I/O port data directions
        stx 0    ;
        ldx #$3E ; LORAM = 0
        stx 1    ; switch out C64 BASIC ROM at $A000-$BFFF for RAM
        
        ldx #$44 ; unmap all C65 ROMs except $e000-$ffff
        stx $d030


; restore BASIC ROM after all other exit handlers have completed
;
; KNOWN ISSUE (unverified on MEGA65; not fixed): exit() and _Exit still have to
; run after this restore, and they, or the data they use, can be linked where a
; ROM has just come back ($A000-$BFFF, and $C000-$CFFF with the C65 ROM
; restore below) - programs over roughly 32 KB. Their code would then be
; invisible and the CPU would run ROM bytes. The c64 and c128 had the same
; defect and now switch the ROM back in only when returning to BASIC (see
; c64/unmap-basic.S, c128/init-mmu.S). A MEGA65 version needs testing first:
; SYS code on the 45GS02 may use a 16-bit stack pointer, which would change
; where BASIC's return address is.
.section .fini.990,"ax", @progbits
        ldx #$3F ; LORAM = 1
        stx 1    ; switch in BASIC ROM at $A000-$BFFF

        ; restore C65 ROMs to as before
        ldx #$64
        stx $d030
        
	cli


