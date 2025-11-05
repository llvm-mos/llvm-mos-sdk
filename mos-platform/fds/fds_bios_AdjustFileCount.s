.include "bios_func.inc"
.text

;
; char fds_bios_AdjustFileCount (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_AdjustFileCount
fds_bios_AdjustFileCount:
  pointerfunc __ADJUST_FILE_COUNT
  rts
