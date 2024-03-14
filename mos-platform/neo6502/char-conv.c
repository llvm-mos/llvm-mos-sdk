// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <ctype.h>
#include <neo6502.h>

// Neo6502 uses CR line endings instead of LF.

__attribute__((always_inline, weak)) void __from_ascii(char c,
                                                       void (*write)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    write('\r');
  else
    write(c);
}

__attribute__((always_inline, weak)) int __to_ascii(int (*read)(void)) {
  int c = read();
  if (__builtin_expect(c == '\r', 0))
    return '\n';
  return c;
}
