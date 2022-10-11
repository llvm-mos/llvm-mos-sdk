#ifndef _PADLIB_H
#define _PADLIB_H

#ifdef __cplusplus
extern "C" {
#endif

// written by Doug Fraker 2019
// NES powerpad code

// pass it 0 or 1, which port
// returns 2 byte value
__attribute((leaf)) unsigned read_powerpad(char pad);

// for side B, powerpad
// ,---------+---------.
// | POWER PAD  side B |
// |  (1) (2) (3) (4)  |
// |                   |
// |  (5) (6) (7) (8)  |
// |                   |
// |  (9) (10)(11)(12) |
// |                   |
// `-------------------'

// 4-2 3-1 12-5 8-9 x-6 x-10 x-11 x-7

#define POWERPAD_4 0x8000
#define POWERPAD_2 0x4000
#define POWERPAD_3 0x2000
#define POWERPAD_1 0x1000
#define POWERPAD_12 0x0800
#define POWERPAD_5 0x0400
#define POWERPAD_8 0x0200
#define POWERPAD_9 0x0100

#define POWERPAD_6 0x0040
#define POWERPAD_10 0x0010
#define POWERPAD_11 0x0004
#define POWERPAD_7 0x0001

#ifdef __cplusplus
}
#endif

#endif // _PADLIB_H
