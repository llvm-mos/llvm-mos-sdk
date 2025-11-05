.text

__fds_bios_CheckFileCount:
  jsr __CHECK_FILE_COUNT
  .word $ADDE
  rts

;
; char fds_bios_CheckFileCount (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_CheckFileCount
fds_bios_CheckFileCount:
  ldx __rc2
  stx [__fds_bios_CheckFileCount+3]
  ldx __rc3
  stx [__fds_bios_CheckFileCount+4]
  jmp __fds_bios_CheckFileCount
