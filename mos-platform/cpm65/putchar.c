/* Fallback putchar used by the llvm-mos libc.
 *
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license. See the LICENSE file in the project
 * root for the full text.
 */

#include <stdio.h>
#include <cpm.h>

void __putchar(char c) {
  if (__builtin_expect(c == '\n', 0))
  	cpm_conout('\r');
  cpm_conout(c);
}

