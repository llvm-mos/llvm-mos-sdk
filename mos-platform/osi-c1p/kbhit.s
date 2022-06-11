; Copyright 2022 LLVM-MOS Project
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
;
; This module is based on the corresponding cc65 osic1p kbhit.s module as of
; commit 5aa75ae81f07724ef8c16d61e42b74a20296acae, and was modified for the
; use in llvm-mos-sdk:
;
; https://github.com/cc65/cc65/blob/5aa75ae81f07724ef8c16d61e42b74a20296acae/libsrc/osic1p/kbhit.s.
; 
; The original cc65 license was:
; 
; This software is provided 'as-is', without any express or implied warranty.
; In no event will the authors be held liable for any damages arising from
; the use of this software.
; 
; Permission is granted to anyone to use this software for any purpose,
; including commercial applications, and to alter it and redistribute it
; freely, subject to the following restrictions:
;
; 1. The origin of this software must not be misrepresented; you must not
; claim that you wrote the original software. If you use this software in
; a product, an acknowledgment in the product documentation would be
; appreciated but is not required.
; 
; 2. Altered source versions must be plainly marked as such, and must not
; be misrepresented as being the original software.
; 
; 3. This notice may not be removed or altered from any source distribution. 


; The method to detect a pressed key is based on the documentation in
; "Section 3 Programmed Key Functions" in "The Challenger Character Graphics
; Reference Manual"
; We only want to return true for characters that can be returned by getchar(),
; but not for keys like <Shift> or <Ctrl>. Therefore a special handling is
; needed for the first row. This is implemented by a bit mask that is stored
; in KBDTMP and that is set to zero after the first round.

; Put keyboard state into dedicated zero-page storage.
;
; "za" attribute means:
;       "z": allocate in page zero
;       "a": section is "allocatable", must be allocated a runtime address
.section .lowmemkbd,"za",@nobits

; Internal state that needs to be preserved across calls.
; The getchar() function uses __CHARBUF to retrieve
; the return value.
.global __CHARBUF
__CHARBUF:      .ds.b    1       ; Character buffer
LASTSCAN:       .ds.b    1       ; Result of previous keyboard scan
DBNCCNT:        .ds.b    1       ; Debounce counter
KBDTMP:         .ds.b    1       ; Temporary values
CTRLSHIFT:      .ds.b    1       ; State of CTRL and SHIFT keys

KBD             = $DF00          ; Polled keyboard register

; Initialize one-character buffer that is filled by kbhit().
; Must be called before main().
.section .text.initkbhit
.global __initkbhit
__initkbhit:
        lda     #$00
        sta     __CHARBUF       ; No character in buffer initially
        sta     LASTSCAN        ; Initialize keyboard state
        sta     DBNCCNT
        sta     KBDTMP
        sta     CTRLSHIFT

        rts

; Routine to get character from keyboard and return it in A.
; Based on the OSI ROM routine at $FD00 but uses different
; storage locations.

.section .text.kbhit
.global __kbhit
__kbhit:
        lda     __CHARBUF       ; Check for previously saved character
        beq     LFD05
        rts                     ; A contains non-zero character code meaning true
LFD05:  lda     #$80            ; Bit mask for initial keyboard row
LFD06:  jsr     LFCBE           ; Write keyboard row
        jsr     LFCC6           ; Read keyboard column
        bne     LFD13           ; Branch if a key in this column was pressed
        lsr     a               ; Otherwise shift mask to next row
        bne     LFD06           ; If not done yet, check next row
        beq     LFD3A           ; Branch if last row reached and no key pressed
LFD13:  lsr     a               ; Have a key press. Shift LSB into carry
        bcc     LFD1F           ; Branch if no key pressed in column 0
        txa                     ; Key pressed in row zero. Get the column data
        and     #$20            ; Mask only the bit for <ESC> as it is the only key in row zero that returns key press
        beq     LFD3A           ; Branch if <ESC> was not the key
        lda     #$1B            ; Set character to <ESC>
        bne     LFD50           ; Do more processing
LFD1F:  jsr     LFE86           ; Shift to find bit that is set (in Y)
        tya                     ; Get bit
        sta     KBDTMP          ; Save it
        asl     a               ; Multiply by 7 by shifting left three times (X8)...
        asl     a
        asl     a
        sec                     ; ...then subtracting one
        sbc     KBDTMP
        sta     KBDTMP          ; Save value*7 for later lookup in table
        txa                     ; Get the keyboard column
        lsr     a               ; Shift out bit zero (only key there is <SHIFT LOCK>)
        asl     a               ; And shift back
        jsr     LFE86           ; Shift to find bit that is set (in Y)
        beq     LFD47           ; Branch if no keys pressed
        lda     #$00
LFD3A:  sta     CTRLSHIFT       ; Save state of <CTRL> and shift keys
LFD3D:  sta     LASTSCAN
        lda     #$02            ; Count used for key debouncing
        sta     DBNCCNT
        lda     #$00            ; Return false
        sta     __CHARBUF
        rts
LFD47:  clc
        tya                     ; Get bit number of pressed key
        adc     KBDTMP          ; Add previously calculated offset for keyboard row*7
        tay
        lda     LFF3B,y         ; Read ASCII code for key from table
LFD50:  cmp     LASTSCAN        ; Debounce - same as last key scan?
        bne     LFD3D           ; If not, try again
        dec     DBNCCNT         ; Decrement debounce counter
        beq     LFD5F           ; Branch if done debouncing
        jsr     LFCDF           ; Wait for short delay to debounce keyboard
        beq     __kbhit         ; Go back and scan keyboard.
LFD5F:  ldx     #$64            ; Was <CONTROL> key down?
        cmp     CTRLSHIFT
        bne     LFD68           ; Branch if not
        ldx     #$0F
LFD68:  stx     DBNCCNT
        sta     CTRLSHIFT
        cmp     #$21
        bmi     LFDD0           ; Done, return key
        cmp     #$5F
        beq     LFDD0           ; Done, return key
        lda     #$01
        jsr     LFCBE           ; Write keyboard row
        jsr     LFCCF           ; Read keyboard column
        sta     KBDTMP
        tax
        and     #$06
        bne     LFDA2
        bit     LASTSCAN
        bvc     LFDBB
        txa
        eor     #$01
        and     #$01
        beq     LFDBB
        lda     #$20
        bit     KBDTMP
        bvc     LFDC3
        lda     #$C0
        bne     LFDC3
LFDA2:  bit     LASTSCAN
        bvc     LFDAA
        txa
        beq     LFDBB
LFDAA:  ldy     LASTSCAN
        cpy     #$31
        bcc     LFDB9
        cpy     #$3C
        bcs     LFDB9
        lda     #$F0
        bne     LFDBB
LFDB9:  lda     #$10
LFDBB:  bit     KBDTMP
        bvc     LFDC3
        clc
        adc     #$C0
LFDC3:  clc
        adc     LASTSCAN
        and     #$7F
        bit     KBDTMP
        bpl     LFDD0
        ora     #$80
LFDD0:  sta     KBDTMP          ; Save pressed key and return in __CHARBUF
        sta     __CHARBUF
        rts

; Write keyboard row with value in A.
; Invert the bits before writing.
; Returns original value of A.

LFCBE:  eor     #$FF
        sta     KBD
        eor     #$FF
        rts

; Read keyboard column and return in X.
; Sets Z flag if no keys were pressed.
; Saves current value of A.

LFCC6:  pha                     ; Save A
        jsr     LFCCF           ; Read keyboard column
        tax                     ; Save in X
        pla                     ; Restore A
        dex                     ; Decrement and then increment to
        inx                     ; preserve value of X but set flags
        rts

; Read keyboard column.
; Invert the bits (pressed key(s) will show up as ones).

LFCCF:  lda     KBD             ; Read keyboard hardware
        eor     #$FF            ; Invert the bits
        rts

; Short fixed delay routine.

LFCDF:  ldy     #$10
LFCE1:  ldx     #$40
LFCE3:  dex
        bne     LFCE3
        dey
        bne     LFCE1
        rts

; Shift A left until we find a 1 in the most significant bit.
; Return the bit number in Y.

LFE86:  ldy     #$08
LFE88:  dey
        asl     a
        bcc     LFE88
        rts

; Lookup table of keyboard keys for each scan row.
LFF3B:  .byte   $BD
        .byte   'P', ';', '/', ' ', 'Z', 'A', 'Q'
        .byte   ',', 'M', 'N', 'B', 'V', 'C', 'X'
        .byte   'K', 'J', 'H', 'G', 'F', 'D', 'S'
        .byte   'I', 'U', 'Y', 'T', 'R', 'E', 'W'
        .byte   $00, $00, $0D, $0A, 'O', 'L', '.'
        .byte   $00, '_', '-', ':', '0', '9', '8'
        .byte   '7', '6', '5', '4', '3', '2', '1'
