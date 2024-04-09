; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Ullrich von Bassewitz, 16.11.2002
;
; File name handling for CBM file I/O
;

        .globl         fnparse, fnparsename, fnset
        .globl         fnadd, fnaddmode, fncomplete, fndefunit
        .globl         fnunit, fnlen, fnisfile, fncmd, fnbuf

        .include        "imag.inc"


;------------------------------------------------------------------------------
; fnparsename: Parse a filename (without drive spec) passed in in rs1 and y.

fnparsename:

        lda     #0
        sta     __rc10         ; Remember length of name

nameloop:
        lda     (__rc2),y       ; Get next char from filename
        beq     namedone        ; Jump if end of name reached

; Check the maximum length, store the character

        ldx     __rc10
        cpx     #16             ; Maximum length reached?
        bcs     invalidname
        lda     (__rc2),y        ; Reload char
        jsr     fnadd           ; Add character to name
        iny                     ; Next char from name
        inc     __rc10          ; Increment length of name
        bne     nameloop        ; Branch always

; Invalid file name

invalidname:
        lda     #33             ; Invalid file name

; Done, we've successfully parsed the name.

namedone:
        rts


;------------------------------------------------------------------------------
; fnparse: Parse a full filename passed in in a/x. Will set the following
; variables:
;
;       fnlen   -> length of filename
;       fnbuf   -> filename including drive spec
;       fnunit  -> unit from spec or default unit
;
; Returns an error code in A or zero if all is ok.

fnparse:

        sta     __rc2
        stx     __rc3            ; Save pointer to name

; For now we will always use the default unit

        jsr     fndefunit

; Check the name for a drive spec

        ldy     #0
        lda     (__rc2),y
        cmp     #'0'
        beq     digit
        cmp     #'1'
        bne     nodrive

digit:  sta     fnbuf+0
        iny
        lda     (__rc2),y
        cmp     #':'
        bne     nodrive

; We found a drive spec, copy it to the buffer

        sta     fnbuf+1
        iny                     ; Skip colon
        bne     drivedone       ; Branch always

; We did not find a drive spec, always use drive zero

nodrive:
        lda     #'0'
        sta     fnbuf+0
        lda     #':'
        sta     fnbuf+1
        ldy     #$00            ; Reposition to start of name

; Drive spec done. We do now have a drive spec in the buffer.

drivedone:
        lda     #2              ; Length of drive spec
        sta     fnlen

; Assume this is a standard file on disk

        sta     fnisfile

; Special treatment for directory. If the file name is "$", things are
; actually different: $ is directory for unit 0, $0 dito, $1 is directory
; for unit 1. For simplicity, we won't check anything else if the first
; character of the file name is '$'.

        lda     (__rc2),y       ; Get first character
        cmp     #'$'            ;
        bne     fnparsename

; Juggle stuff

        ldx     fnbuf+0         ; unit
        stx     fnbuf+1
        sta     fnbuf+0

; Add the file mask

        lda     #':'
        sta     fnbuf+2
        lda     #'*'
        sta     fnbuf+3
        lda     #4
        sta     fnlen

; No need to check the name. Length is already 2

        lda     #0              ; ok flag
        sta     fnisfile        ; This is not a real file
        rts

;--------------------------------------------------------------------------
; fndefunit: Use the default unit

fndefunit:

        lda     curunit
        sta     fnunit
        rts

;--------------------------------------------------------------------------
; fnset: Tell the kernal about the file name

fnset:

        lda     fnlen
        ldx     #<fnbuf
        ldy     #>fnbuf
        jmp     SETNAM

;--------------------------------------------------------------------------
; fncomplete: Complete a filename by adding ",t,m" where t is the file type
; and m is the access mode passed in in the A register
;
; fnaddmode: Add ",m" to a filename, where "m" is passed in A

fncomplete:
        pha                     ; Save mode
        lda     __filetype
        jsr     fnaddmode       ; Add the type
        pla
fnaddmode:
        pha
        lda     #','
        jsr     fnadd
        pla

fnadd:  ldx     fnlen
        inc     fnlen
        sta     fnbuf,x
        rts

;--------------------------------------------------------------------------
; Data

.bss

fnunit:         .fill    1
fnlen:          .fill    1
fnisfile:       .fill    1      ; Flags standard file (as opposed to "$")

.data
fncmd:          .byte   'S'     ; Use as scratch command
fnbuf:          .fill    35     ; Either 0:0123456789012345,t,m
                                ; Or     0:0123456789012345=0123456789012345
