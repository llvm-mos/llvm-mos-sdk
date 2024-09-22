/***********************************************************************
 * crt0.c
 *
 * This file contains the implemantation of the "C" definition of
 * init and fini code and the directory entry and info sector for
 * use in GEOS applications  with llvm-mos C compiler.
 *
 ***********************************************************************/

#include "geos.h"

asm(".set __zp_reg_size, 0xfb - 0x90 \n"
    ".section .data \n"
    "__userzp_copy:	.space __zp_reg_size+1 \n"
    ".section .text  \n"
    ".global __swap_userzp \n"
    "__swap_userzp: \n"
    "     php                             ; save all registers and flags \n"
    "     pha \n"
    "     txa \n"
    "     pha \n"
    "     tya \n"
    "     pha \n"
    "     ldx     # __zp_reg_size           ; $FA..$90 \n"
    "__swaploop: \n"
    "     ldy     __zp_reg_start,x        ; load zp byte \n"
    "     lda     __userzp_copy,x         ; load buffer byte \n"
    "     sta     __zp_reg_start,x        ; store zp byte \n"
    "     tya \n"
    "     sta     __userzp_copy,x         ; store buffer byte \n"
    "     dex \n"
    "     bpl     __swaploop \n"
    "     pla                             ; restore all registers and flags \n"
    "     tay \n"
    "     pla \n"
    "     tax \n"
    "     pla \n"
    "     plp \n"
    "     rts \n");

asm(".section .init.010,\"axR\",@progbits \n"
    "jsr __swap_userzp \n");

asm(".global __after_main\n"
    ".section .after_main,\"axR\",@progbits\n"
    "__after_main:\n"
    "     jsr __swap_userzp\n"
    "     jmp __EnterDeskTop\n");

void EnterDeskTop(void) {
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jmp __EnterDeskTop\n");
}

__attribute__((section(".dir_block"))) retain __attribute__((
    weak)) cvt_dir_entry_t __std_dir_entry = {{USR,
                                               {0, 0xff},
                                               "llvm-mos VLIR   ",
                                               {0, 0xff},
                                               VLIR,
                                               APPLICATION,
                                               {24, 07, 01, 0, 0},
                                               0},
                                              "PRG formatted GEOS file V1.0"};

__attribute__((section(".info_block"))) retain __attribute__((
    weak)) file_header_t __std_file_header = {
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
    ""};
