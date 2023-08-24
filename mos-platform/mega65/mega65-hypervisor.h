// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from KickC. Modified from original version.

/*
 * MIT License
 *
 * Copyright (c) 2017 Jesper Gravgaard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _MEGA65_HYPERVISOR_H
#define _MEGA65_HYPERVISOR_H

#ifdef __cplusplus
extern "C" {
#endif

// MEGA65 HyperVisor

// TRAP Writing triggers hypervisor trap $00
#define htrap00 (*(volatile char *)0xd640)
// TRAP Writing triggers hypervisor trap $01
#define htrap01 (*(volatile char *)0xd641)
// TRAP Writing triggers hypervisor trap $02
#define htrap02 (*(volatile char *)0xd642)
// TRAP Writing triggers hypervisor trap $03
#define htrap03 (*(volatile char *)0xd643)
// TRAP Writing triggers hypervisor trap $04
#define htrap04 (*(volatile char *)0xd644)
// TRAP Writing triggers hypervisor trap $05
#define htrap05 (*(volatile char *)0xd645)
// TRAP Writing triggers hypervisor trap $06
#define htrap06 (*(volatile char *)0xd646)
// TRAP Writing triggers hypervisor trap $07
#define htrap07 (*(volatile char *)0xd647)
// TRAP Writing triggers hypervisor trap $08
#define htrap08 (*(volatile char *)0xd648)
// TRAP Writing triggers hypervisor trap $09
#define htrap09 (*(volatile char *)0xd649)
// TRAP Writing triggers hypervisor trap $0a
#define htrap0a (*(volatile char *)0xd64a)
// TRAP Writing triggers hypervisor trap $0b
#define htrap0b (*(volatile char *)0xd64b)
// TRAP Writing triggers hypervisor trap $0c
#define htrap0c (*(volatile char *)0xd64c)
// TRAP writing triggers hypervisor trap $0d
#define htrap0d (*(volatile char *)0xd64d)
// TRAP Writing triggers hypervisor trap $0e
#define htrap0e (*(volatile char *)0xd64e)
// TRAP Writing triggers hypervisor trap $0f
#define htrap0f (*(volatile char *)0xd64f)

// TRAP Writing triggers hypervisor trap $10
#define htrap10 (*(volatile char *)0xd650)
// TRAP Writing triggers hypervisor trap $11
#define htrap11 (*(volatile char *)0xd651)
// TRAP Writing triggers hypervisor trap $12
#define htrap12 (*(volatile char *)0xd652)
// TRAP Writing triggers hypervisor trap $13
#define htrap13 (*(volatile char *)0xd653)
// TRAP Writing triggers hypervisor trap $14
#define htrap14 (*(volatile char *)0xd654)
// TRAP Writing triggers hypervisor trap $15
#define htrap15 (*(volatile char *)0xd655)
// TRAP Writing triggers hypervisor trap $16
#define htrap16 (*(volatile char *)0xd656)
// TRAP Writing triggers hypervisor trap $17
#define htrap17 (*(volatile char *)0xd657)
// TRAP Writing triggers hypervisor trap $18
#define htrap18 (*(volatile char *)0xd658)
// TRAP Writing triggers hypervisor trap $19
#define htrap19 (*(volatile char *)0xd659)
// TRAP Writing triggers hypervisor trap $1a
#define htrap1a (*(volatile char *)0xd65a)
// TRAP Writing triggers hypervisor trap $1b
#define htrap1b (*(volatile char *)0xd65b)
// TRAP Writing triggers hypervisor trap $1c
#define htrap1c (*(volatile char *)0xd65c)
// TRAP Writing triggers hypervisor trap $1d
#define htrap1d (*(volatile char *)0xd65d)
// TRAP Writing triggers hypervisor trap $1e
#define htrap1e (*(volatile char *)0xd65e)
// TRAP Writing triggers hypervisor trap $1f
#define htrap1f (*(volatile char *)0xd65f)

// TRAP Writing triggers hypervisor trap $20
#define htrap20 (*(volatile char *)0xd660)
// TRAP Writing triggers hypervisor trap $21
#define htrap21 (*(volatile char *)0xd661)
// TRAP Writing triggers hypervisor trap $22
#define htrap22 (*(volatile char *)0xd662)
// TRAP Writing triggers hypervisor trap $23
#define htrap23 (*(volatile char *)0xd663)
// TRAP Writing triggers hypervisor trap $24
#define htrap24 (*(volatile char *)0xd664)
// TRAP Writing triggers hypervisor trap $25
#define htrap25 (*(volatile char *)0xd665)
// TRAP Writing triggers hypervisor trap $26
#define htrap26 (*(volatile char *)0xd666)
// TRAP Writing triggers hypervisor trap $27
#define htrap27 (*(volatile char *)0xd667)
// TRAP Writing triggers hypervisor trap $28
#define htrap28 (*(volatile char *)0xd668)
// TRAP Writing triggers hypervisor trap $29
#define htrap29 (*(volatile char *)0xd669)
// TRAP Writing triggers hypervisor trap $2a
#define htrap2a (*(volatile char *)0xd66a)
// TRAP Writing triggers hypervisor trap $2b
#define htrap2b (*(volatile char *)0xd66b)
// TRAP Writing triggers hypervisor trap $2c
#define htrap2c (*(volatile char *)0xd66c)
// TRAP Writing triggers hypervisor trap $2d
#define htrap2d (*(volatile char *)0xd66d)
// TRAP Writing triggers hypervisor trap $2e
#define htrap2e (*(volatile char *)0xd66e)
// TRAP Writing triggers hypervisor trap $2f
#define htrap2f (*(volatile char *)0xd66f)

// TRAP Writing triggers hypervisor trap $30
#define htrap30 (*(volatile char *)0xd670)
// TRAP Writing triggers hypervisor trap $31
#define htrap31 (*(volatile char *)0xd671)
// TRAP Writing triggers hypervisor trap $32
#define htrap32 (*(volatile char *)0xd672)
// TRAP Writing triggers hypervisor trap $33
#define htrap33 (*(volatile char *)0xd673)
// TRAP Writing triggers hypervisor trap $34
#define htrap34 (*(volatile char *)0xd674)
// TRAP Writing triggers hypervisor trap $35
#define htrap35 (*(volatile char *)0xd675)
// TRAP Writing triggers hypervisor trap $36
#define htrap36 (*(volatile char *)0xd676)
// TRAP Writing triggers hypervisor trap $37
#define htrap37 (*(volatile char *)0xd677)
// TRAP Writing triggers hypervisor trap $38
#define htrap38 (*(volatile char *)0xd678)
// TRAP Writing triggers hypervisor trap $39
#define htrap39 (*(volatile char *)0xd679)
// TRAP Writing triggers hypervisor trap $3a
#define htrap3a (*(volatile char *)0xd67a)
// TRAP Writing triggers hypervisor trap $3b
#define htrap3b (*(volatile char *)0xd67b)
// TRAP Writing triggers hypervisor trap $3c
#define htrap3c (*(volatile char *)0xd67c)
// TRAP Writing triggers hypervisor trap $3d
#define htrap3d (*(volatile char *)0xd67d)
// TRAP Writing triggers hypervisor trap $3e
#define htrap3e (*(volatile char *)0xd67e)
// TRAP Writing triggers hypervisor trap $3f
#define htrap3f (*(volatile char *)0xd67f)

#ifdef __cplusplus
}
#endif
#endif // _MEGA65_HYPERVISOR_H
