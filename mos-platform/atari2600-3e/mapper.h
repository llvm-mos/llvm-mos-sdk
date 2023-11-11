/* TigerVision (3E) mapper include files */

#ifndef MAPPER_H
#define MAPPER_H

#define MAPPER_TYPE_3E

#define MAPPER_BANKED_ROM
#define MAPPER_BANKED_ROM_SIZE 0x800

#define MAPPER_XRAM
#define MAPPER_XRAM_SIZE 0x400
#define MAPPER_XRAM_READ 0x1000
#define MAPPER_XRAM_WRITE 0x1400

#define MAPPER_CART_ROM_KB(kb) \
    asm(".globl __cart_rom_size\n__cart_rom_size = " #kb)

#include <mapper_rom_single.h>
#include <mapper_xram_single.h>

typedef unsigned char bank_index_t;

#endif
