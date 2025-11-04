; BIOS license check bypass.
; When loading from disk, there should be a file
; set to load at $2000 containing a single byte
; with bit 7 set to 1. This will enable vblank NMIs,
; which will call the BIOS NMI handler which redirects
; to the third custom handler by default.
; By setting the below code as the initial third
; NMI handler, we can disable NMIs again, set our
; actual handler, and jump into our program before the
; BIOS attempts to check for the license text.
.text
.weak bypass
bypass:
  lda #$00
  sta $2000
  lda #<nmi_user_3
  sta $DFFA
  lda #>nmi_user_3
  sta $DFFB
  lda #$35
  sta $0102
  lda #$AC
  sta $0103
  jmp ($FFFC)
