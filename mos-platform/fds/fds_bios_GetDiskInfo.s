.include "bios_func.inc"
.text

;
; char fds_bios_GetDiskInfo (struct fds_bios_disk_id *disk_id);
;
.global fds_bios_GetDiskInfo
fds_bios_GetDiskInfo:
  pointerfunc __GET_DISK_INFO
  rts
