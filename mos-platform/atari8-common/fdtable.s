; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Christian Groessler, May-2000
;
; fd indirection table & helper functions
;

        .include "atari.inc"
        .include "fd.inc"
        .include "imag.inc"

        .globl clriocb
        .globl fdtoiocb_down
        .globl fddecusage
        .globl newfd

; gets fd in ax, decrements usage counter
; return iocb index in X
; return N bit set for invalid fd
; return Z bit set if last user
; all registers destroyed
fdtoiocb_down:

        cpx     #0
        bne     inval
        cmp     #MAX_FD_INDEX
        bcs     inval
        tax
        lda     fd_index,x              ; get index
        tay
        lda     #$ff
        sta     fd_index,x              ; clear entry
        tya
        asl     a                       ; create index into fd table
        asl     a
        tax
        lda     #$ff
        cmp     fd_table+ft_iocb,x      ; entry in use?
        beq     inval                   ; no, return error
        lda     fd_table+ft_usa,x       ; get usage counter
        beq     ok_notlast              ; 0? (shouldn't happen)
        sec
        sbc     #1                      ; decr usage counter
        sta     fd_table+ft_usa,x
retiocb:php
        txa
        tay
        lda     fd_table+ft_iocb,x      ; get iocb
        tax
        plp
        bne     cont
        lda     #$ff
        sta     fd_table+ft_iocb,y      ; clear table entry
        lda     fd_table+ft_flag,y
        and     #16                     ; opened by app?
        eor     #16                     ; return set Z if yes
cont:   rts

ok_notlast:
        lda     #1                      ; clears Z
        jmp     retiocb

inval:  ldx     #$ff                    ; sets N
        rts


; clear iocb except for ICHID field
; expects X to be index to IOCB (0,$10,$20,etc.)
; all registers destroyed

clriocb:

        inx                     ; don't clear ICHID
        ldy     #15
        lda     #0
loop:   sta     ICHID,x
        inx
        dey
        bne     loop
        rts


; decrements usage counter for fd
; if 0 reached, it's marked as unused
; get fd index in tmp2
; Y register preserved
fddecusage:

        lda     __rc11                  ; get fd
        cmp     #MAX_FD_INDEX
        bcs     ret                     ; invalid index, do nothing
        tax
        lda     fd_index,x
        pha
        lda     #$ff
        sta     fd_index,x
        pla
        asl     a                       ; create index into fd table
        asl     a
        tax
        lda     #$ff
        cmp     fd_table+ft_iocb,x      ; entry in use?
        beq     ret                     ; no, do nothing
        lda     fd_table+ft_usa,x       ; get usage counter
        beq     ret                     ; 0? should not happen
        sec
        sbc     #1                      ; decrement by one
        sta     fd_table+ft_usa,x
        bne     ret                     ; not 0
        lda     #$ff                    ; 0, table entry unused now
        sta     fd_table+ft_iocb,x      ; clear table entry
ret:    rts


; newfd
;
; called from open() function
; finds a fd to use for an open request
; checks whether it's a device or file (file: characters follow the ':')
; files always get an exclusive slot
; for devices it is checked whether the device is already open, and if yes,
; a link to this open device is returned
;
; Calling parameters:
;       tmp3 - length of filename + 1
;       AX   - points to filename
;       Y    - iocb to use (if we need a new open)
; Return parameters:
;       tmp2 - fd num ($ff and C=0 in case of error - no free slot)
;       C    - 0/1 for no open needed/open should be performed
; all registers preserved!

        .bss

; local variables:
loc_Y:          .fill   1
loc_ptr4_l:     .fill   1
loc_ptr4_h:     .fill   1
loc_tmp1:       .fill   1
loc_devnum:     .fill   1
loc_size:       .fill   1

        .text

newfd:

        pha
        txa
        pha
        tya
        pha

        ldx     #0
        stx     loc_devnum
        lda     __rc10
        sta     loc_tmp1
        stx     __rc10          ; init tmp1
        stx     __rc11          ; init tmp2
        lda     __rc9
        sta     loc_ptr4_h
        lda     __rc8
        sta     loc_ptr4_l
        pla
        sta     loc_Y
        pla
        sta     __rc9
        pla
        sta     __rc8

        ; ptr4 points to filename

        ldy     #1
        lda     #':'
        cmp     (__rc8),y      ; "X:"
        beq     colon1
        iny
        cmp     (__rc8),y      ; "Xn:"
        beq     colon2

        ; no colon there!? OK, then we use a fresh iocb....
        ; return error here? no, the subsequent open call should fail

do_open_nd:     ; do open and don't remember device
        lda     #2
        sta     __rc10
do_open:lda     __rc10
        ora     #1
        sta     __rc10          ; set flag to return 'open needed' : C = 1
        ldx     #ft_iocb
        ldy     #$ff
srchfree:
        tya
        cmp     fd_table,x      ; check ft_iocb field for $ff
        beq     freefnd         ; found a free slot
        txa
        clc
        adc     #ft_entrylen
        tax
        cmp     #(MAX_FD_VAL*4)+ft_iocb ; end of table reached?
        bcc     srchfree

; error: no free slot found
noslot: ldx     #0
        stx     __rc10          ; return with C = 0
        dex
        stx     __rc11          ; iocb: $ff marks error
        jmp     finish

; found a free slot
freefnd:txa
        sec
        sbc     #ft_iocb        ; normalize
        tax
        lsr     a
        lsr     a
        sta     __rc11          ; return fd
        lda     #2
        bit     __rc10          ; remember device?
        beq     l1              ; yes
        lda     #0              ; no, put 0 in field
        beq     l2

l1:     lda     loc_devnum              ; get device
l2:     sta     fd_table+ft_dev,x       ; set device
        lda     #1
        sta     fd_table+ft_usa,x       ; set usage counter
        lda     loc_Y
        sta     fd_table+ft_iocb,x      ; set iocb index
        lda     loc_devnum
        and     #7                      ; device number is 3 bits
        ora     #16                     ; indicated a fd actively opened by the app
        sta     fd_table+ft_flag,x
        lda     __rc11
        jsr     fdt_to_fdi              ; get new index
noslot1:bcs     noslot                  ; no one available (noslot1: helper label for branch out of range)
        ;cmp    #$ff                    ; no one available
        ;beq    noslot  ;@@@ cleanup needed
        sta     __rc11                  ; return index
        jmp     finish

; string in "Xn:xxx" format
colon2: dey
        lda     (__rc8),y       ; get device number
        sec
        sbc     #'0'
        and     #7
        sta     loc_devnum
        sta     __rc11          ; save it for speed later here also
        lda     #4              ; max. length if only  device + number ("Xn:")
        cmp     __rc12
        bcc     do_open_nd      ; string is longer -> contains filename
        bcs     check_dev       ; handle device only string

; string in "X:xxx" format
colon1: lda     #3              ; max. length if device only ("X:")
        cmp     __rc12
        bcc     do_open_nd      ; string is longer -> contains filename

; get device and search it in fd table
check_dev:
        ldy     #0
        lda     (__rc8),y       ; get device id
        tay
        ldx     #(MAX_FD_VAL*4) - ft_entrylen
srchdev:lda     #$ff
        cmp     fd_table+ft_iocb,x      ; is entry valid?
        beq     srch2                   ; no, skip this entry
        tya
        cmp     fd_table+ft_dev,x
        beq     fnddev
srch2:  txa
        sec
        sbc     #ft_entrylen+1
        tax
        bpl     srchdev

; not found, open new iocb
        jmp     do_open

; found device in table, check device number (e.g R0 - R3)
fnddev: lda     fd_table+ft_flag,x
        and     #7
        cmp     __rc11                  ; contains devnum
        bne     srch2                   ; different device numbers

; found existing open iocb with same device
        txa
        lsr     a
        lsr     a
        sta     __rc11
        inc     fd_table+ft_usa,x       ; increment usage counter
        jsr     fdt_to_fdi              ; get new index
        bcs     noslot1                 ; no one available
        sta     __rc11                  ; return index

; clean up and go home
finish: lda     __rc8
        pha
        lda     __rc9
        pha
        lda     loc_Y
        pha
        lda     __rc10
        pha
        lda     loc_tmp1
        sta     __rc10
        pla
        lsr     a                       ; set C as needed

        pla
        tay
        pla
        tax
        pla
        rts

