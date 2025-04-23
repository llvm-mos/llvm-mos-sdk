; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; 2002-11-16, Ullrich von Bassewitz
; 2013-12-23, Greg King
;
; int read (int fd, void* buf, unsigned count);
;

        .globl          read

        .include        "cbm.inc"
        .include        "errno.inc"
        .include        "fcntl.inc"
        .include        "filedes.inc"
        .include        "imag.inc"


;--------------------------------------------------------------------------
; initstdin: Open the stdin file descriptors for the keyboard

.section .init,"ax",@progbits
  jsr initstdin

.text
initstdin:

        lda     #STDIN_FILENO + LFN_OFFS
        ldx     #CBMDEV_KBD
        ldy     #$FF
        jsr     SETLFS
        jmp     OPEN            ; Will always succeed

;--------------------------------------------------------------------------
; read

read:

        jsr     rwcommon        ; Pop params, check handle
        bcs     invalidfd       ; Invalid handle

; Check if the LFN is valid and the file is open for writing

        adc     #LFN_OFFS       ; Carry is already clear
        tax
        lda     fdtab-LFN_OFFS,x; Get flags for this handle
        tay
        and     #LFN_READ       ; File open for writing?
        beq     invalidfd

; Check the EOF flag. If it is set, don't read anything

        tya                     ; Get flags again
        bmi     eof

; Remember the device number.

        ldy     unittab-LFN_OFFS,x
        sty     unit

; Valid lfn. Make it the input file

        jsr     CHKIN
        bcc     5f              ; Branch if ok
        jmp     __mappederrno   ; Store into __oserror, map to errno, return -1

; Read the next byte

1:      jsr     BASIN
        sta     __rc10          ; Save the input byte
        ldx     unit
        bne     2f              ; Not keyboard/screen-editor
        cmp     #$0D            ; Is it a Carriage Return?
        bne     2f
        jsr     BSOUT           ; Yes, echo it (because editor didn't)

2:      jsr     READST          ; Read the IEEE status
        sta     __rc12          ; Save it
        and     #%10111111      ; Check anything but the EOI bit
        bne     devnotpresent   ; Assume device not present

; Store the byte just read

        ldy     #0
        lda     __rc10
        sta     (__rc2),y
        inc     __rc2
        bne     3f
        inc     __rc3           ; *buf++ = A;

; Increment the byte count

3:      inc     __rc6
        bne     4f
        inc     __rc7

; Get the status again and check the EOI bit

4:      lda     __rc12
        and     #%01000000      ; Check for EOI
        bne     6f              ; Jump if end of file reached

; Decrement the count

5:      dec     __rc4
        bne     1b
        dec     __rc5
        bne     1b
        beq     done            ; Branch always

; Set the EOI flag and bail out

6:      ldx     __rc11          ; Get the handle
        lda     #LFN_EOF
        ora     fdtab,x
        sta     fdtab,x

; Read done, close the input channel

done:   jsr     CLRCH

; Clear __oserror and return the number of chars read

eof:    lda     #0
        sta     __oserror
        lda     __rc6
        ldx     __rc7
        rts

; Error entry: Device not present

devnotpresent:
        lda     #ENODEV
        .byte   $2C             ; Skip next opcode via BIT <abs>

; Error entry: The given file descriptor is not valid or not open

invalidfd:
        lda     #EBADF
        jmp     __directerrno   ; Sets _errno, clears __oserror, returns -1

;--------------------------------------------------------------------------

.bss

unit:   .fill    1
