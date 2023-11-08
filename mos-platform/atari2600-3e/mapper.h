/* TigerVision (3E) mapper include files */

#define MAPPER_TYPE_3E

#define MAPPER_BANKED_ROM
#define MAPPER_BANKED_ROM_SIZE 0x800

#define MAPPER_XRAM
#define MAPPER_XRAM_SIZE 0x400
#define MAPPER_XRAM_READ 0x1000
#define MAPPER_XRAM_WRITE 0x1400

#include <mapper_base.h>
#include <mapper_xram.h>
