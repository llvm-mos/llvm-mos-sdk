; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

; Ullrich von Bassewitz, 16.11.2002
;
; int open (const char* name, int flags, ...);  /* May take a mode argument */


        .include        "errno.inc"
        .include        "fcntl.inc"
        .include        "filedes.inc"


;--------------------------------------------------------------------------
; closeallfiles: Close all open files.

; This must happen after fclosing all stdio files.

.section .fini.200,"ax",@progbits
closeallfiles:

        ldx     #MAX_FDS-1
loop:   lda     fdtab,x
        beq     next            ; Skip unused entries

; Close this file

        txa
        pha                     ; Save current value of X
        ldx     #0
        jsr     close
        pla
        tax

; Next file

next:   dex
        bpl     loop

;--------------------------------------------------------------------------
; open

.text
.globl open
open:

; Push the flags

        pha

; Translate the filename to PETSCII

        jsr _translate_filename

; Save the flags into __rc12

        pla
        sta     __rc12

; Parse the filename. Bail out if is not ok

        lda     __rc2
        ldx     __rc3
        jsr     fnparse         ; Parse it
        tax
        bne     oserror         ; Bail out if problem with name

; Get a free file handle and remember it in __rc11

        jsr     freefd
        lda     #EMFILE         ; Load error code
        bcs     seterrno        ; Jump in case of errors
        stx     __rc11

; Check the flags. We cannot have both, read and write flags set, and we cannot
; open a file for writing without creating it.

        lda     __rc12
        and     #(O_RDWR | O_CREAT)
        cmp     #O_RDONLY       ; Open for reading?
        beq     doread          ; Yes: Branch
        cmp     #(O_WRONLY | O_CREAT)   ; Open for writing?
        beq     dowrite

; Invalid open mode

        lda     #EINVAL

; Error entry. Sets _errno, clears __oserror, returns -1

seterrno:
        jmp     __directerrno

; Error entry: Close the file and exit. OS error code is in A on entry

closeandexit:
        pha
        lda     __rc11
        clc
        adc     #LFN_OFFS
        jsr     CLOSE
        ldx     fnunit
        jsr     closecmdchannel
        pla

; Error entry: Set oserror and errno using error code in A and return -1

oserror:jmp     __mappederrno

; Read bit is set. Add an 'R' to the name

doread: lda     #'R'
        jsr     fnaddmode       ; Add the mode to the name
        lda     #LFN_READ
        bne     common          ; Branch always

; If O_TRUNC is set, scratch the file, but ignore any errors

dowrite:
        lda     __rc12
        and     #O_TRUNC
        beq     notrunc
        jsr     scratch

; Complete the file name. Check for append mode here.

notrunc:
        lda     __rc12            ; Get the mode again
        and     #O_APPEND       ; Append mode?
        bne     append          ; Branch if yes

; Setup the name for create mode

        lda     #'W'
        jsr     fncomplete      ; Add type and mode to the name
        jmp     appendcreate

; Append bit is set. Add an 'A' to the name

append: lda     #'A'
        jsr     fnaddmode       ; Add open mode to file name
appendcreate:
        lda     #LFN_WRITE

; Common read/write code. Flags in A, handle in __rc11

common: sta     __rc12
        jsr     fnset           ; Set the file name

        lda     __rc11
        clc
        adc     #LFN_OFFS
        ldx     fnunit
        ldy     fnisfile        ; Is this a standard file on disk?
        beq     nofile          ; Branch if not
        tay                     ; Use the LFN also as SA for files
nofile:                         ; ... else use SA=0 (read)
        jsr     SETLFS          ; Set the file params

        jsr     OPEN
        bcs     oserror

; Open the drive command channel and read it

        ldx     fnunit
        jsr     opencmdchannel
        bne     closeandexit
        ldx     fnunit
        jsr     readdiskerror
        bne     closeandexit    ; Branch on error

; File is open. Mark it as open in the table

        ldx     __rc11
        lda     __rc12
        sta     fdtab,x
        lda     fnunit
        sta     unittab,x       ; Remember

; Done. Return the handle in a/x

        txa                     ; Handle
        ldx     #0
        stx     __oserror      ; Clear __oserror
        rts
