.section .text.ft_push_music_bank,"ax",@progbits
.globl __push_music_bank
__push_music_bank:
  lda mos8(__is_music_banked)
  beq .Lpush_skip
  lda __FT_SONG_LIST_H
  jsr __get_prg_bank
  sta mos8(__saved_music_bank)
.Lpush_skip:
  rts

.section .text.ft_pop_music_bank,"ax",@progbits
.globl __pop_music_bank
__pop_music_bank:
  lda mos8(__is_music_banked)
  beq .Lpop_skip
  lda mos8(__saved_music_bank)
  ldx __FT_SONG_LIST_H
  jsr __set_prg_bank
.Lpop_skip:
	rts

.section .text.ft_banked_music_init,"ax",@progbits
.globl __banked_music_init
.weak banked_music_init
__banked_music_init:
banked_music_init:
  ldx #1
  stx mos8(__is_music_banked)
  pha
  lda mos8(__rc3)
  sta __FT_SONG_LIST_H
  jsr __push_music_bank
  jsr music_init
  jmp __pop_music_bank

.section .text.ft_unbank_music,"ax",@progbits
.globl __unbank_music
__unbank_music:
  lda #0
  sta mos8(__is_music_banked)
  rts
