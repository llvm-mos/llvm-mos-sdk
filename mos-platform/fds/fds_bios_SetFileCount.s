.include "bios_func.inc"
.text

;
; char fds_bios_SetFileCount (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_SetFileCount
fds_bios_SetFileCount:
  pointerfunc __SET_FILE_COUNT
  rts
