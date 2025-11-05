.text

__fds_bios_GetDiskInfo:
  jsr __GET_DISK_INFO
  .word $ADDE
  rts

;
; char fds_bios_GetDiskInfo (struct fds_bios_disk_id *disk_id);
;
.global fds_bios_GetDiskInfo
fds_bios_GetDiskInfo:
  lda __rc2
  sta [__fds_bios_GetDiskInfo+3]
  lda __rc3
  sta [__fds_bios_GetDiskInfo+4]
  jsr __fds_bios_GetDiskInfo
  rts
