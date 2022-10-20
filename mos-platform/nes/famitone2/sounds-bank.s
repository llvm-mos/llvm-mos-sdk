.section .text.ft_push_sounds_bank,"ax",@progbits
.globl __push_sounds_bank
__push_sounds_bank:
  lda mos8(__are_sounds_banked)
  beq .Lpush_skip
  lda __FT_SONG_LIST_H
  jsr __get_prg_bank
  sta mos8(__saved_sounds_bank)
.Lpush_skip:
  rts

.section .text.ft_pop_sounds_bank,"ax",@progbits
.globl __pop_sounds_bank
__pop_sounds_bank:
  lda mos8(__are_sounds_banked)
  beq .Lpop_skip
  lda mos8(__saved_sounds_bank)
  ldx __FT_SONG_LIST_H
  jsr __set_prg_bank
.Lpop_skip:
	rts

.section .text.ft_banked_sounds_init,"ax",@progbits
.globl __banked_sounds_init
.weak banked_sounds_iniprg_rom_t
__banked_sounds_init:
banked_sounds_init:
  ldx #1
  stx mos8(__are_sounds_banked)
  pha
  lda mos8(__rc3)
  sta __FT_SONG_LIST_H
  jsr __push_sounds_bank
  jsr sounds_init
  jmp __pop_sounds_bank

.section .text.ft_unbank_sounds,"ax",@progbits
.globl __unbank_sounds
__unbank_sounds:
  lda #0
  sta mos8(__are_sounds_banked)
  rts
