.text

__fds_bios_WriteFile:
  jsr __WRITE_FILE
  .word $ADDE
  .word $EFBE
  rts

;
; char fds_bios_WriteFile (struct fds_bios_disk_id *disk_id, struct fds_bios_file_header *file_header, char file_num);
;
.global fds_bios_WriteFile
fds_bios_WriteFile:
  ldx __rc2
  stx [__fds_bios_WriteFile+3]
  ldx __rc3
  stx [__fds_bios_WriteFile+4]
  ldx __rc4
  stx [__fds_bios_WriteFile+5]
  ldx __rc5
  stx [__fds_bios_WriteFile+6]
  jmp __fds_bios_WriteFile
