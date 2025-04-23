/***********************************************************************
 * crt0.c
 *
 * This file contains the implemantation of the "C" definition of
 * init and fini code and the directory entry and info sector for
 * use in GEOS applications  with llvm-mos C compiler.
 *
 ***********************************************************************/

#include "geos.h"


asm(R"ASM(
    .set __zp_reg_size, 0xfb - 0x90
    .section .data
    __userzp_copy:	.space __zp_reg_size+1
    .section .text 
    .global __swap_userzp 
    __swap_userzp:
         php                             ; save all registers and flags 
         pha 
         txa 
         pha
         tya 
         pha 
         ldx     # __zp_reg_size         ; $FA..$90
    __swaploop:
         ldy     __zp_reg_start,x        ; load zp byte 
         lda     __userzp_copy,x         ; load buffer byte 
         sta     __zp_reg_start,x        ; store zp byte 
         tya 
         sta     __userzp_copy,x         ; store buffer byte 
         dex 
         bpl     __swaploop 
         pla                             ; restore all registers and flags
         tay 
         pla 
         tax
         pla
         plp
         rts
    )ASM");

asm(R"ASM(
    .section .init.010,"ax",@progbits
    jsr __swap_userzp
)ASM");

asm(R"ASM(
                 .global __after_main
                 .section .after_main,"ax",@progbits
   __after_main: jsr __swap_userzp
                 jmp __EnterDeskTop
)ASM");

void EnterDeskTop(void) {
  __attribute__((leaf)) asm volatile("jsr __swap_userzp \n"
                                     "jmp __EnterDeskTop\n");
}

__attribute__((section(".dir_block"), retain, weak))
cvt_dir_entry_t __std_dir_entry = {
    {USR,
    {0, 0xff},
    "llvm-mos VLIR   ",
    {0, 0xff},
    VLIR,
    APPLICATION,
    {24, 07, 01, 0, 0},
    0},
    "PRG formatted GEOS file V1.0"
};

__attribute__((section(".info_block"), retain, weak)) 
file_header_t __std_file_header = {
    3,
    21,
    0x80 | 63,
    {
        0b11111111, 0b11111111, 0b11111111, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b10000000, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000001,
        0b11111111, 0b11111111, 0b11111111,
    },
    0x80 | USR,
    APPLICATION,
    VLIR,
    0x0400,
    0x03ff,
    0x0400,
    "geoVLIR AP  V0.0\000\000\000",
    0,
    "<Name of Programmer>",
    "",
    "",
    ""
};
