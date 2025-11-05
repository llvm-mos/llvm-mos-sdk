.text

__fds_bios_AppendFile:
  jsr __APPEND_FILE
  .word $ADDE
  .word $EFBE
  rts

;
; char fds_bios_AppendFile (struct fds_bios_disk_id *disk_id, struct fds_bios_file_header *file_header);
;
.global fds_bios_AppendFile
fds_bios_AppendFile:
  lda __rc2
  sta [__fds_bios_AppendFile+3]
  lda __rc3
  sta [__fds_bios_AppendFile+4]
  lda __rc4
  sta [__fds_bios_AppendFile+5]
  lda __rc5
  sta [__fds_bios_AppendFile+6]
  jmp __fds_bios_AppendFile
