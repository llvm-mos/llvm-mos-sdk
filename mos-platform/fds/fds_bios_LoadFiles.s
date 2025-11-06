.include "bios_func.inc"
.text

;
; char fds_bios_LoadFiles (struct fds_bios_disk_id *disk_id, char *file_ids, char *loaded);
;
.global fds_bios_LoadFiles
fds_bios_LoadFiles:
  pointerfunc __LOAD_FILES, 2
  bne 1f
  pha
  tya
  ldy #0
  sta (__rc6),y
  pla
1:
  rts
