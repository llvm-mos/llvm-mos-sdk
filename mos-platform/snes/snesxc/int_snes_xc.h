
#ifndef __INT_SNES_XC_H
#define __INT_SNES_XC_H

typedef __INT8_TYPE__   int8_t;
typedef __INT16_TYPE__  int16_t;
typedef __INT32_TYPE__  int32_t;
typedef __UINT8_TYPE__  uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __SIZE_TYPE__ size_t;

#ifndef NULL
#define NULL 0
#endif

typedef volatile int8_t *volatile vs8;
typedef volatile int16_t *volatile vs16;
typedef volatile int32_t *volatile vs32;
typedef volatile uint8_t *volatile vu8;
typedef volatile uint16_t *volatile vu16;
typedef volatile uint32_t *volatile vu32;

#endif // __INT_SNES_XC_H
