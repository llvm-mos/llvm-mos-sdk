.include "bios_func.inc"
.text

;
; char fds_bios_WriteFile (struct fds_bios_disk_id *disk_id, struct fds_bios_file_header *file_header, char file_num);
;
.global fds_bios_WriteFile
fds_bios_WriteFile:
  pointerfunc __WRITE_FILE, 2
  rts
