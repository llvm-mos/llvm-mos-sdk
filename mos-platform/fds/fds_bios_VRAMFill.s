.text

;
; void fds_bios_VRAMFill (char tile_row, char value, char rows_attr);
;
.global fds_bios_VRAMFill
fds_bios_VRAMFill:
  ldy __rc2
  jsr __VRAM_FILL
  rts
