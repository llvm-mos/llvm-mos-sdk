#ifndef _MAPPER_MACROS_H
#define _MAPPER_MACROS_H

#include <mapper.h>

#define MAPPER_CART_ROM_KB(kb) \
    asm(".globl __cart_rom_size\n__cart_rom_size = " #kb)

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#ifdef MAPPER_BANKED_ROM
// section attribute doesn't seem to recognize C "concatenated" "strings"
#define _CODE_BANK(index) __attribute__((section(".rom" index ".code")))
#define CODE_BANK(index) _CODE_BANK(STRINGIFY(index))
#define _RODATA_BANK(index) __attribute__((section(".rom" index ".rodata")))
#define RODATA_BANK(index) _RODATA_BANK(STRINGIFY(index))
#else
#define CODE_BANK(index)
#define RODATA_BANK(index)
#endif

#endif

