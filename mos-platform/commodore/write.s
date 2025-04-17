; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 16.11.2002
;
; int write (int fd, const void* buf, unsigned count);
;

        .globl          write

        .include        "cbm.inc"
        .include        "errno.inc"
        .include        "fcntl.inc"
        .include        "filedes.inc"
        .include        "imag.inc"


;--------------------------------------------------------------------------
; initstdout: Open the stdout and stderr file descriptors for the screen.

.section .init,"ax",@progbits
  jsr initstdout

.text
initstdout:

        lda     #STDOUT_FILENO + LFN_OFFS
        jsr     1f
        lda     #STDERR_FILENO + LFN_OFFS
1:      ldx     #CBMDEV_SCREEN
        ldy     #$FF
        jsr     SETLFS
        jmp     OPEN            ; Will always succeed

;--------------------------------------------------------------------------
; write

.globl write
write:

        jsr     rwcommon        ; Pop params, check handle
        bcs     invalidfd       ; Invalid handle

; Check if the LFN is valid and the file is open for writing

        adc     #LFN_OFFS       ; Carry is already clear
        tax
        lda     fdtab-LFN_OFFS,x; Get flags for this handle
        and     #LFN_WRITE      ; File open for writing?
        beq     invalidfd

; Valid lfn. Make it the output file

        jsr     CKOUT
        bcc     3f
.Lerror:
        jmp     __mappederrno   ; Store into __oserror, map to errno, return -1

; Output the next character from the buffer

1:      ldy     #0
        lda     (__rc2),y
        inc     __rc2
        bne     2f
        inc     __rc3           ; A = *buf++;
2:      jsr     BSOUT

; Check the status

        pha
        jsr     READST
        lsr     a               ; Bit zero is write timeout
        bne     devnotpresent2
        pla
        bcs     4f

; Count characters written

        inc     __rc6
        bne     3f
        inc     __rc7

; Decrement count

3:      dec     __rc4
        bne     1b
        dec     __rc5
        bne     1b

; Wrote all chars or disk full. Close the output channel

4:      jsr     CLRCH

; Clear __oserror and return the number of chars written

        lda     #0
        sta     __oserror
        lda     __rc6
        ldx     __rc7
        rts

; Error entry: Device not present

devnotpresent2:
        pla
devnotpresent:
        lda     #ENODEV
        .byte   $2C             ; Skip next opcode via BIT <abs>

; Error entry: The given file descriptor is not valid or not open

invalidfd:
        lda     #EBADF
        jmp     __directerrno   ; Sets _errno, clears __oserror, returns -1
