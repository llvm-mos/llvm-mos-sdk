// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

unsigned char __zp __iodat;
unsigned char __zp __iodir;
unsigned char __zp __viddma;
unsigned char __zp __sprsys;

unsigned char  __zp _FileStartBlock;
unsigned short __zp _FileBlockOffset;
unsigned char  __zp _FileExecFlag;
unsigned short __zp _FileDestAddr;
unsigned short __zp _FileFileLen;

unsigned char  __zp _FileCurrBlock;
unsigned short __zp _FileBlockByte;
unsigned short __zp _FileDestPtr;

unsigned char  __zp SndSema;
unsigned short __zp SndPtrTmp;
unsigned short __zp SndTmp;  
unsigned short __zp SndEnvPtr;

unsigned char  __zp IntVal;