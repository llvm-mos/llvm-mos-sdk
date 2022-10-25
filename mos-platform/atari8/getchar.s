.include "atari.inc"

;
; int getchar(void);
;
.global getchar
getchar:
  lda #GETCHR
  sta ICCOM
  ldx #0
  stx ICBLL
  stx ICBLH
  jsr CIOV
; X is preserved as zero
  bmi error
  cmp #EOL
  bne ret
  lda #'\n'
ret:
  rts

error:
  dex
  txa
  rts
