.text

;
; void fds_bios_MemFill (char value, char start, char end);
;
.global fds_bios_MemFill
fds_bios_MemFill:
  ldy __rc2
  jmp __MEM_FILL
