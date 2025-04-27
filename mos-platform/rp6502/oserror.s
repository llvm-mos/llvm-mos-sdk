; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; 2000-05-17, Ullrich von Bassewitz
; 2014-05-28, Greg King
;
; int __fastcall__ __osmaperrno (unsigned char oserror);
; /* Map a system-specific error into a system-independent code. */
;

        .include        "errno.inc"

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

        API_ENOENT   = 1
        API_ENOMEM   = 2
        API_EACCES   = 3
        API_ENODEV   = 4
        API_EMFILE   = 5
        API_EBUSY    = 6
        API_EINVAL   = 7
        API_ENOSPC   = 8
        API_EEXIST   = 9
        API_EAGAIN   = 10
        API_EIO      = 11
        API_EINTR    = 12
        API_ENOSYS   = 13
        API_ESPIPE   = 14
        API_ERANGE   = 15
        API_EBADF    = 16
        API_ENOEXEC  = 17
        API_EUNKNOWN = 18

        FR_DISK_ERR            = 33
        FR_INT_ERR             = 34
        FR_NOT_READY           = 35
        FR_NO_FILE             = 36
        FR_NO_PATH             = 37
        FR_INVALID_NAME        = 38
        FR_DENIED              = 39
        FR_EXIST               = 40
        FR_INVALID_OBJECT      = 41
        FR_WRITE_PROTECTED     = 42
        FR_INVALID_DRIVE       = 43
        FR_NOT_ENABLED         = 44
        FR_NO_FILESYSTEM       = 45
        FR_MKFS_ABORTED        = 46
        FR_TIMEOUT             = 47
        FR_LOCKED              = 48
        FR_NOT_ENOUGH_CORE     = 49
        FR_TOO_MANY_OPEN_FILES = 50
        FR_INVALID_PARAMETER   = 51

ErrTab:
        .byte API_ENOENT             , ENOENT
        .byte API_ENOMEM             , ENOMEM
        .byte API_EACCES             , EACCES
        .byte API_ENODEV             , ENODEV
        .byte API_EMFILE             , EMFILE
        .byte API_EBUSY              , EBUSY
        .byte API_EINVAL             , EINVAL
        .byte API_ENOSPC             , ENOSPC
        .byte API_EEXIST             , EEXIST
        .byte API_EAGAIN             , EAGAIN
        .byte API_EIO                , EIO
        .byte API_EINTR              , EINTR
        .byte API_ENOSYS             , ENOSYS
        .byte API_ESPIPE             , ESPIPE
        .byte API_ERANGE             , ERANGE
        .byte API_EBADF              , EBADF
        .byte API_ENOEXEC            , ENOEXEC
      ; .byte API_EUNKNOWN           , EUNKNOWN
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
