.include "bios_func.inc"
.text

;
; char fds_bios_AppendFile (struct fds_bios_disk_id *disk_id, struct fds_bios_file_header *file_header);
;
.global fds_bios_AppendFile
fds_bios_AppendFile:
  pointerfunc __APPEND_FILE, 2
  rts
