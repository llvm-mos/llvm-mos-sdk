.section .init.010,"axR",@progbits
; Clear decimal mode
        cld

.section .init.050,"axR",@progbits
; Initialization Loop:
; * Clears Atari 2600 whole memory (128 bytes) including BSS segment
; * Clears TIA registers
; * Sets system stack pointer to $ff (i.e top of zero-page)
        ldx     #0
        txa
clearLoop:
        dex
        txs
        pha
        bne     clearLoop

.section .call_main.100,"axR",@progbits
        jmp     main

; TODO: how do we get rid of "jsr main" in crt0?
;.section .init.400,"axR",@progbits
;	jmp	main
