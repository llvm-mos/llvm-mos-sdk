.text

;
; void fds_bios_Delayms (char delay);
;
.global fds_bios_Delayms
fds_bios_Delayms:
  tay
  jmp __DELAY_MS
