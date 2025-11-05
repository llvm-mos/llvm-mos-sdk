.text

__fds_bios_SetFileCount:
  jsr __SET_FILE_COUNT
  .word $ADDE
  rts

;
; char fds_bios_SetFileCount (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_SetFileCount
fds_bios_SetFileCount:
  ldx __rc2
  stx [__fds_bios_SetFileCount+3]
  ldx __rc3
  stx [__fds_bios_SetFileCount+4]
  jsr __fds_bios_SetFileCount
  rts
