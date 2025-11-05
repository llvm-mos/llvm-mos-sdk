.include "bios_func.inc"
.text

;
; char fds_bios_CheckFileCount (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_CheckFileCount
fds_bios_CheckFileCount:
  pointerfunc __CHECK_FILE_COUNT
  rts
