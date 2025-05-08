; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; 2000-05-17, Ullrich von Bassewitz
; 2014-05-28, Greg King
;
; int __osmaperrno (unsigned char oserror);
; /* Map a system-specific error into a system-independent code. */
;

        .include        "errno.inc"
        .include        "rp6502.inc"

.text
.globl __osmaperrno
__osmaperrno:
        ldx     #ErrTabSize
1:      cmp     ErrTab-2,x      ; Search for the error code
        beq     1f              ; Jump if found
        dex
        dex
        bne     1b              ; Next entry

; Code not found, return EUNKNOWN

        lda     #<EUNKNOWN
        ldx     #>EUNKNOWN
        rts

; Found the code

1:      lda     ErrTab-1,x
        ldx     #$00            ; High byte always zero
        rts

.rodata

ErrTab:
        .byte RIA_ENOENT             , ENOENT
        .byte RIA_ENOMEM             , ENOMEM
        .byte RIA_EACCES             , EACCES
        .byte RIA_ENODEV             , ENODEV
        .byte RIA_EMFILE             , EMFILE
        .byte RIA_EBUSY              , EBUSY
        .byte RIA_EINVAL             , EINVAL
        .byte RIA_ENOSPC             , ENOSPC
        .byte RIA_EEXIST             , EEXIST
        .byte RIA_EAGAIN             , EAGAIN
        .byte RIA_EIO                , EIO
        .byte RIA_EINTR              , EINTR
        .byte RIA_ENOSYS             , ENOSYS
        .byte RIA_ESPIPE             , ESPIPE
        .byte RIA_ERANGE             , ERANGE
        .byte RIA_EBADF              , EBADF
        .byte RIA_ENOEXEC            , ENOEXEC
      ; .byte RIA_EUNKNOWN           , EUNKNOWN
        .byte FR_DISK_ERR            , EIO
      ; .byte FR_INT_ERR             , EUNKNOWN
        .byte FR_NOT_READY           , EBUSY
        .byte FR_NO_FILE             , ENOENT
        .byte FR_NO_PATH             , ENOENT
        .byte FR_INVALID_NAME        , EINVAL
        .byte FR_DENIED              , EACCES
        .byte FR_EXIST               , EEXIST
        .byte FR_INVALID_OBJECT      , EINVAL
        .byte FR_WRITE_PROTECTED     , EACCES
        .byte FR_INVALID_DRIVE       , ENODEV
      ; .byte FR_NOT_ENABLED         , EUNKNOWN
      ; .byte FR_NO_FILESYSTEM       , EUNKNOWN
      ; .byte FR_MKFS_ABORTED        , EUNKNOWN
      ; .byte FR_TIMEOUT             , EUNKNOWN
        .byte FR_LOCKED              , EBUSY
        .byte FR_NOT_ENOUGH_CORE     , ENOMEM
        .byte FR_TOO_MANY_OPEN_FILES , EMFILE
        .byte FR_INVALID_PARAMETER   , EINVAL

ErrTabSize = . - ErrTab
