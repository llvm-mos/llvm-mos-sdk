; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 16.11.2002
;
; int __fastcall__ close (int fd);
;

        .globl         close

        .include        "errno.inc"
        .include        "filedes.inc"
        .include        "imag.inc"


;--------------------------------------------------------------------------
; _close

close:

; Check if we have a valid handle

        cpx     #$00
        bne     invalidfd
        cmp     #MAX_FDS        ; Is it valid?
        bcs     invalidfd       ; Jump if no
        sta     __rc11          ; Save the handle

; Check if the file is actually open

        tax
        lda     fdtab,x         ; Get flags for this handle
        and     #LFN_OPEN
        beq     invalidfd

; Valid lfn, close it. The close call is always error free, at least as far
; as the kernal is involved

        lda     #LFN_CLOSED
        sta     fdtab,x
        txa                     ; Get handle
        clc
        adc     #LFN_OFFS       ; Make LFN from handle
        jsr     CLOSE

; Read the drive error channel, then close it

        ldy     __rc11          ; Get the handle
        ldx     unittab,y       ; Get the disk for this handle
        jsr     readdiskerror   ; Read the disk error code
        pha                     ; Save it on stack
        ldy     __rc11
        ldx     unittab,y
        jsr     closecmdchannel ; Close the disk command channel
        pla                     ; Get the error code from the disk
        jmp     __mappederrno  ; Set __oserror and _errno, return 0/-1

; Error entry: The given file descriptor is not valid or not open

invalidfd:
        lda     #EBADF
        jmp     __directerrno  ; Set _errno, clear __oserror, return -1
