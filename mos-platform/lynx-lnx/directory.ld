/*
Copyright 2025 LLVM-MOS Project
Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
information.
*/

/* Provides single directory entry main/resident section */

/*
    BYTE  | Block
    SHORT | Offset in block
    BYTE  | 0x88
    SHORT | Address to load
    SHORT | Length of data to load
*/

/* Segment 0 contains all the resident/non-swappped code */
BYTE ((__DIRECTORYSTART__ + SIZEOF(.directory)) / (__BLOCKSIZE__))
SHORT((__DIRECTORYSTART__ + SIZEOF(.directory)) & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(ADDR(.text))
SHORT(ADDR(.bss) - ADDR(.text))

/* Segment 1's offset is the length of everything on the catridge so far... */
SEG1 = SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data) + SIZEOF(.zp.data) + (__SEGMENTCOUNT__*8) + SIZEOF(.secbootldr) + SIZEOF(.bootldr);
BYTE(SEG1 / __BLOCKSIZE__)
SHORT(SEG1 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART1__)
SHORT(SIZEOF(.segment1))

/* Segment 2++ is the previous segment's offset + the size of the previous segment */
SEG2 = SEG1+SIZEOF(.segment1);
BYTE(SEG2 / __BLOCKSIZE__)
SHORT(SEG2 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART2__)
SHORT(SIZEOF(.segment2))

SEG3 = SEG2+SIZEOF(.segment2);
BYTE(SEG3 / __BLOCKSIZE__)
SHORT(SEG3 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART3__)
SHORT(SIZEOF(.segment3))

SEG4 = SEG3+SIZEOF(.segment3);
BYTE(SEG4 / __BLOCKSIZE__)
SHORT(SEG4 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART4__)
SHORT(SIZEOF(.segment4))

SEG5 = SEG4+SIZEOF(.segment4);
BYTE(SEG5 / __BLOCKSIZE__)
SHORT(SEG5 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART5__)
SHORT(SIZEOF(.segment5))

SEG6 = SEG5+SIZEOF(.segment5);
BYTE(SEG6 / __BLOCKSIZE__)
SHORT(SEG6 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART6__)
SHORT(SIZEOF(.segment6))

SEG7 = SEG6+SIZEOF(.segment6);
BYTE(SEG7 / __BLOCKSIZE__)
SHORT(SEG7 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART7__)
SHORT(SIZEOF(.segment7))

SEG8 = SEG7+SIZEOF(.segment7);
BYTE(SEG8 / __BLOCKSIZE__)
SHORT(SEG8 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART8__)
SHORT(SIZEOF(.segment8))

SEG9 = SEG8+SIZEOF(.segment8);
BYTE(SEG9 / __BLOCKSIZE__)
SHORT(SEG9 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART9__)
SHORT(SIZEOF(.segment9))

SEG10 = SEG9+SIZEOF(.segment9);
BYTE(SEG10 / __BLOCKSIZE__)
SHORT(SEG10 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART10__)
SHORT(SIZEOF(.segment10))

SEG11 = SEG10+SIZEOF(.segment10);
BYTE(SEG11 / __BLOCKSIZE__)
SHORT(SEG11 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART11__)
SHORT(SIZEOF(.segment11))

SEG12 = SEG11+SIZEOF(.segment11);
BYTE(SEG12 / __BLOCKSIZE__)
SHORT(SEG12 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART12__)
SHORT(SIZEOF(.segment12))

SEG13 = SEG12+SIZEOF(.segment12);
BYTE(SEG13 / __BLOCKSIZE__)
SHORT(SEG13 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART13__)
SHORT(SIZEOF(.segment13))

SEG14 = SEG13+SIZEOF(.segment13);
BYTE(SEG14 / __BLOCKSIZE__)
SHORT(SEG14 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART14__)
SHORT(SIZEOF(.segment14))

SEG15 = SEG14+SIZEOF(.segment14);
BYTE(SEG15 / __BLOCKSIZE__)
SHORT(SEG15 & (__BLOCKSIZE__ - 1))
BYTE(0x88)
SHORT(__SEGMENTSTART15__)
SHORT(SIZEOF(.segment15))
