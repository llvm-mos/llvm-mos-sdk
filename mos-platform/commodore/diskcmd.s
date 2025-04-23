; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 2002-11-17, 2009-02-22
;
; Handle disk command channels
;

        .globl         isdisk
        .globl         opencmdchannel
        .globl         closecmdchannel
        .globl         readdiskerror
        .globl         writediskcmd
        .globl         writefndiskcmd

        .include        "cbm.inc"
        .include        "filedes.inc"
        .include        "imag.inc"

;--------------------------------------------------------------------------
; isdisk: Return carry clear if the unit number in X is a disk, return
; carry set if not.

isdisk:

        cpx     #FIRST_DRIVE    ; Disk unit?
        bcc     1f              ; Branch if no disk
        cpx     #FIRST_DRIVE+MAX_DRIVES
        rts

1:      sec
        rts

;--------------------------------------------------------------------------
; Open the command channel for the disk unit in X. The function returns an
; error code in A and sets the flags according to the contents of A.

opencmdchannel:

        jsr     isdisk          ; Disk unit?
        bcs     success

; Is this channel already open?

        ldy     opentab-FIRST_DRIVE,x
        bne     isopen

; Open the command channel, Carry is still clear

        stx     __rc10          ; Save the unit number
        txa                     ; Get unit number
        adc     #(LFN_OFFS+MAX_FDS-FIRST_DRIVE)
        ldy     #15             ; Secondary address for cmd channel
        jsr     SETLFS

        lda     #0
        jsr     SETNAM          ; No name supplied to OPEN

        jsr     OPEN
        bcs     done            ; Error, code is in A

; Command channel is open now. Increment the count

        ldx     __rc10          ; Unit number
        ldy     opentab-FIRST_DRIVE,x
isopen: iny
        tya
        sta     opentab-FIRST_DRIVE,x

; Done, return success

success:lda     #$00
done:   cmp     #$00            ; Set flags for return code
        rts


;--------------------------------------------------------------------------
; closecmdchannel: Decrement the counter for the disk command channel and
; close the channel if the counter drops to zero. The function expects the
; drive number in X and returns an error code in A. The flags for the return
; code are set when the function returns.

closecmdchannel:

        jsr     isdisk          ; Disk unit?
        bcs     success

; Is this channel really open?

        ldy     opentab-FIRST_DRIVE,x
        beq     success         ; OOPS! Channel is not open

; Decrement the count and stor it back

        dey
        tya
        sta     opentab-FIRST_DRIVE,x

; If the counter is now zero, close the channel. We still have carry clear
; when we come here.

        bne     success
        txa                     ; Make LFN from drive number
        adc     #(LFN_OFFS+MAX_FDS-FIRST_DRIVE)
        jsr     CLOSE
        bcs     done
        bcc     success

;--------------------------------------------------------------------------
; readdiskerror: Read a disk error from an already open command channel.
; Returns an error code in A, which may either be the code read from the
; command channel, or another error when accessing the command channel failed.

readdiskerror:

        jsr     isdisk
        bcs     success

; Read the command channel. We won't check the status after the channel is
; open, because this seems to be unnecessary in most cases.

        txa
        clc                     ; Make LFN from drive number
        adc     #(LFN_OFFS+MAX_FDS-FIRST_DRIVE)
        tax
        jsr     CHKIN           ; Make the command channel input
        bcs     done            ; Bail out with error code in A

        jsr     BASIN
        and     #$0F            ; Make digit value from PETSCII
        sta     __rc10
        asl     a               ; * 2
        asl     a               ; * 4, carry clear
        adc     __rc10          ; * 5
        asl     a               ; * 10
        sta     __rc10

        jsr     BASIN
        and     #$0F            ; Make digit value from PETSCII
        clc
        adc     __rc10

; Errors below 20 are not real errors. Fix that

        cmp     #20+1
        bcs     1f
        lda     #$00
1:      pha

; Read the remainder of the message and throw it away

1:      jsr     BASIN
        cmp     #$0D
        bne     1b

; Close the input channel

        jsr     CLRCH

; Restore the error code (will also set the flags) and return

        pla
        rts

;--------------------------------------------------------------------------
; writefndiskcmd: Write the contents of fncmd to the command channel of the
; drive in fnunit. Returns an error code in A, flags are set according to
; the contents of A.

writefndiskcmd:
        lda     #<fncmd
        sta     __rc2
        lda     #>fncmd
        sta     __rc3

        ldx     fnlen
        inx                     ; Account for command char in fncmd
        txa                     ; Length of name into A
        ldx     fnunit          ; Unit

; Run directly into writediskcmd

;       jmp     writediskcmd

;--------------------------------------------------------------------------
; writediskcmd: Gets pointer to data in rs1, length in A. Writes all data
; to the command channel of the drive in X. Returns an error code in A,
; flags are set according to the contents of A.

writediskcmd:

        jsr     isdisk
        bcs     success         ; No disk - already done

; Remember the length

        sta     __rc10

; Write to the command channel.

        txa
        clc                     ; Make LFN from drive number
        adc     #(LFN_OFFS+MAX_FDS-FIRST_DRIVE)
        tax
        jsr     CKOUT           ; Make the command channel output
        bcs     done            ; Bail out with error code in A

        ldy     #$00
1:      cpy     __rc10
        bcs     1f
        lda     (__rc2),y
        iny
        jsr     BSOUT
        bcc     1b

        pha
        jsr     CLRCH
        pla
        rts

1:      jsr     CLRCH
        lda     #$00
        rts


;--------------------------------------------------------------------------
; Data

.bss

opentab:        .fill    MAX_DRIVES
