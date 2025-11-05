.text

__fds_bios_SetFileCount1:
  jsr __SET_FILE_COUNT_1
  .word $ADDE
  rts

;
; char fds_bios_SetFileCount1 (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_SetFileCount1
fds_bios_SetFileCount1:
  ldx __rc2
  stx [__fds_bios_SetFileCount1+3]
  ldx __rc3
  stx [__fds_bios_SetFileCount1+4]
  jmp __fds_bios_SetFileCount1
