.text

;
; char fds_bios_ReadKeyboard(struct fds_bios_keyboard_data *data);
;
.global fds_bios_ReadKeyboard
fds_bios_ReadKeyboard:
  jsr __READ_KEYBOARD
  pha
  ldx #8
  ldy #8
1:
  lda $0,x
  sta (__rc2),y
  dex
  dey
  bpl 1b
  pla
  rts
