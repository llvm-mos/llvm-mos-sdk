/* 4K ROM */

#ifndef MAPPER_H
#define MAPPER_H

#define MAPPER_TYPE_4K

#define MAPPER_CART_ROM_KB(kb) \
    asm(".globl __cart_rom_size\n__cart_rom_size = " #kb)

#endif
