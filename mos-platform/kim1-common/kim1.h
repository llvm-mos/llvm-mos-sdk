// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// MOS Technology KIM-1 system definitions

#ifndef _KIM1_H
#define _KIM1_H

// Monitor ROM entry points (serial terminal I/O)
#define KIM1_OUTCHR 0x1EA0U // Transmit character in A to serial
#define KIM1_INTCHR 0x1E5AU // Receive character from serial into A

// Monitor ROM entry points (tape I/O)
#define KIM1_DUMPT 0x1800U // Dump memory to tape
#define KIM1_LOADT 0x1873U // Load memory from tape

// Monitor ROM entry points (misc)
#define KIM1_START  0x1C4FU // Enter KIM-1 monitor
#define KIM1_SCANDS 0x1F1FU // Scan 6-digit LED display
#define KIM1_KEYIN  0x1F40U // Open keyboard channel
#define KIM1_GETKEY 0x1F6AU // Return key from keypad (0x00-0x14, 0x15=none)

#endif // _KIM1_H
