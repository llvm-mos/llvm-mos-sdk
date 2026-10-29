// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Portions originally from cc65.

#ifndef _EEPROM_H
#define _EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

 /* Read a 16 bit word from the given address */
unsigned short lynx_eeprom_read(unsigned char cell);

/* Write the word at the given address */
void lynx_eeprom_write(unsigned char cell, unsigned short val);

/* Clear the word at the given address */
void lynx_eeprom_erase(unsigned char cell);

#ifdef __cplusplus
}
#endif

#endif
