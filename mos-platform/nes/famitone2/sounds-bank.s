.section .text.ft_push_sounds_bank,"ax",@progbits
.globl __push_sounds_bank
__push_sounds_bank:
  lda mos8(__are_sounds_banked)
  beq .Lpush_skip
  lda __FT_SFX_ADR_H
  jsr __get_prg_bank
  sta mos8(__saved_sounds_bank)
  lda mos8(__sounds_bank)
  ldx __FT_SFX_ADR_H
  jmp __set_prg_bank
.Lpush_skip:
  rts

.section .text.ft_pop_sounds_bank,"ax",@progbits
.globl __pop_sounds_bank
__pop_sounds_bank:
  lda mos8(__are_sounds_banked)
  beq .Lpop_skip
  lda mos8(__saved_sounds_bank)
  ldx __FT_SFX_ADR_H
  jsr __set_prg_bank
.Lpop_skip:
	rts

.section .text.ft_banked_sounds_init,"ax",@progbits
.globl __banked_sounds_init
.weak banked_sounds_init
__banked_sounds_init:
banked_sounds_init:
  sta mos8(__sounds_bank)
  lda #1
  sta mos8(__are_sounds_banked)
  lda mos8(__rc3)
  sta __FT_SFX_ADR_H
  jsr __push_sounds_bank
	ldx mos8(__rc2)
	ldy mos8(__rc3)
  jsr FamiToneSfxInit
  jmp __pop_sounds_bank

.section .text.ft_unbank_sounds,"ax",@progbits
.globl __unbank_sounds
__unbank_sounds:
  lda #0
  sta mos8(__are_sounds_banked)
  rts
