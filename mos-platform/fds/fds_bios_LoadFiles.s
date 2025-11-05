.text

__fds_bios_LoadFiles:
  jsr __LOAD_FILES
  .word $ADDE
  .word $EFBE
  rts

;
; char fds_bios_LoadFiles (struct fds_bios_disk_id *disk_id, char *file_ids, char *loaded);
;
.global fds_bios_LoadFiles
fds_bios_LoadFiles:
  lda __rc2
  sta [__fds_bios_LoadFiles+3]
  lda __rc3
  sta [__fds_bios_LoadFiles+4]
  lda __rc4
  sta [__fds_bios_LoadFiles+5]
  lda __rc5
  sta [__fds_bios_LoadFiles+6]
  jsr __fds_bios_LoadFiles
  bne 1f
  pha
  tya
  ldy #0
  sta (__rc6),y
  pla
1:
  rts
