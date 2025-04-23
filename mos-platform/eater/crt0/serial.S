; Copyright (c) 2023 Rhys Weatherley
;
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

#define ACIA_DATA   0x5000
#define ACIA_STATUS 0x5001
#define ACIA_CMD    0x5002
#define ACIA_CTRL   0x5003

#define RX_HIGH     240     ; Buffer high water mark.
#define RX_LOW      224     ; Buffer low water mark.

; Initialize the serial port.
.global __do_init_serial
.section .init.270,"ax",@progbits
__do_init_serial:
  lda ACIA_STATUS           ; Clear any reported errors.
  lda ACIA_DATA             ; Empty the receive buffer if something is in it.
  stz ACIA_STATUS           ; Force the ACIA to reset itself.
  lda #$1f                  ; 19200-N-8-1
  sta ACIA_CTRL
  lda #$09                  ; ACIA_TIC1 | ACIA_DTR
  sta ACIA_CMD

; Handle interrupts for serial receive.
.text
.global __serial_isr
.section .text.__serial_isr,"axR",@progbits
__serial_isr:
  lda ACIA_STATUS               ; Is there an ACIA interrupt pending?
  bpl .L__serial_isr_end
  and #$08                      ; Is RDRF set, indicating a received byte?
  beq .L__serial_isr_end
  lda ACIA_DATA                 ; Retrieve the character that just arrived.
  ldx __serial_rx_in            ; Add it to the serial receive buffer.
  sta __serial_rx_buffer,x
  inc __serial_rx_in            ; Advance the buffer pointer.
  lda __serial_rx_in            ; Is the buffer above the high water mark?
  sec
  sbc __serial_rx_out
  cmp #RX_HIGH
  bcc .L__serial_isr_end
  lda #$01                      ; Disable receive interrupts.
  sta ACIA_CMD
.L__serial_isr_end:
  rts

; Get a character from the serial receive buffer.
.global __chrin
.section .text.__chrin,"ax",@progbits
__chrin:
  ldx __serial_rx_out           ; Do we have a character?
  cpx __serial_rx_in
  beq __chrin                   ; No, then go back and wait again.
  inc __serial_rx_out           ; Increment the buffer's output pointer.
  lda __serial_rx_in            ; Are we now below the low water mark?
  sec
  sbc __serial_rx_out
  cmp #RX_LOW
  bcs .L__chrin_have_char
  lda #$09                      ; Turn receive interrupts back on.
  sta ACIA_CMD
.L__chrin_have_char:
  lda __serial_rx_buffer,x
  ldx #0
  rts

; Get a character from the serial receive buffer, without waiting.
.global __chrin_no_wait
.section .text.__chrin_no_wait,"ax",@progbits
__chrin_no_wait:
  ldx __serial_rx_out           ; Do we have a character?
  cpx __serial_rx_in
  beq .L__chrin_no_char
  inc __serial_rx_out           ; Increment the buffer's output pointer.
  lda __serial_rx_in            ; Are we now below the low water mark?
  sec
  sbc __serial_rx_out
  cmp #RX_LOW
  bcs .L__chrin_no_wait_have_char
  lda #$09                      ; Turn receive interrupts back on.
  sta ACIA_CMD
.L__chrin_no_wait_have_char:
  lda __serial_rx_buffer,x
  ldx #0
  rts
.L__chrin_no_char:
  lda #$ff                      ; No character available, return -1.
  tax
  rts

; Put a character to the serial port.
.global __chrout
.section .text.__chrout,"ax",@progbits
__chrout:
  sta ACIA_DATA                 ; Transmit A using the ACIA.
  ldx #$70                      ; Wait ~560us for the byte to be transmitted.
.L__chrout_wait_for_tx:
  dex
  bne .L__chrout_wait_for_tx
  rts

; Control variables for the serial input buffer in the zero page.
.section .zp.bss,"zaw",@nobits
__serial_rx_in:
  .fill 1
__serial_rx_out:
  .fill 1

; Location of the serial input buffer in noinit RAM.
.section .noinit,"aw",@nobits
__serial_rx_buffer:
  .fill 256
