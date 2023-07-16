#ifndef _6502_H
#define _6502_H

#define BRK() __attribute__((leaf)) asm("brk\nnop\n")
#define CLI() __attribute__((leaf)) asm("cli\n")
#define SEI() __attribute__((leaf)) asm("sei\n")

#endif // not _6502_H
