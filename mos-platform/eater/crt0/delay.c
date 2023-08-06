/*
 * Copyright (c) 2023 Rhys Weatherley
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

extern unsigned long millis(void);

void delay(unsigned ms)
{
    if (ms) {
        unsigned long start = millis();
        while ((millis() - start) < ms)
            ; /* do nothing */
    }
}
