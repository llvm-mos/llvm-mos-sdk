.text

__fds_bios_AdjustFileCount:
  jsr __ADJUST_FILE_COUNT
  ; Some BIOS functions require pointers to be provided by specifying them
  ; right after the function call, inline with the rest of the routine.
  ; This means that pointers are typically provided statically;
  ; to make it dynamic and give these functions a more familiar C interface,
  ; we modify the pointer argument during runtime.
  .word $ADDE
  rts

;
; char fds_bios_AdjustFileCount (struct fds_bios_disk_id *disk_id, char count);
;
.global fds_bios_AdjustFileCount
fds_bios_AdjustFileCount:
  ldx __rc2
  stx [__fds_bios_AdjustFileCount+3]
  ldx __rc3
  stx [__fds_bios_AdjustFileCount+4]
  jmp __fds_bios_AdjustFileCount
