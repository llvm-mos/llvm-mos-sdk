.include "bios_func.inc"
.text

;
; char fds_bios_SetFileCount1 (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_SetFileCount1
fds_bios_SetFileCount1:
  pointerfunc __SET_FILE_COUNT_1
  rts
