// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

__attribute__((section(".zp.pal_bg_ptr"))) volatile const char *PAL_BG_PTR;
__attribute__((section(".zp.pal_spr_ptr"))) volatile const char *PAL_SPR_PTR;
__attribute__((section(".zp.pal_update"))) extern volatile char PAL_UPDATE;

extern const char __palBrightTableL[];
extern const char __palBrightTableH[];
void pal_spr_bright(char bright) {
  PAL_SPR_PTR = (const char *)(__palBrightTableH[bright] << 8 |
                               __palBrightTableL[bright]);
  PAL_UPDATE = 1;
}
void pal_bg_bright(char bright) {
  PAL_BG_PTR = (const char *)(__palBrightTableH[bright] << 8 |
                              __palBrightTableL[bright]);
  PAL_UPDATE = 1;
}
void pal_bright(char bright) {
  pal_spr_bright(bright);
  pal_bg_bright(bright);
}
