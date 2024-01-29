
#include <atari2600.h>
#include <vcslib.h>
#include <peekpoke.h>
#include <mapper.h>
#include <string.h>
#include <stdbool.h>

#include "test-lib-emutest.h"

// show a nice message on the CRT so that the emulators are happy

#define KERNEL_BANK 0

/*{w:8,h:16}*/
RODATA_BANK(KERNEL_BANK) const char PFMAP_GOOD[16] = {
  0x3C,0x42,0x81,0x81,0x81,0x42,0x3C,0x00,
  0x41,0x21,0x11,0x0F,0x11,0x21,0x41,0x00
};
/*{w:8,h:16}*/
RODATA_BANK(KERNEL_BANK) const char PFMAP_BAD[16] = {
  0x1F,0x01,0x0F,0x01,0x09,0x14,0x3E,0x22,
  0x22,0x00,0x17,0x12,0x12,0x12,0xF7,0x00
};
/*{w:8,h:16}*/
RODATA_BANK(KERNEL_BANK) const char PFMAP_UNKNOWN[16] = {
  0x18,0x24,0x42,0x42,0x40,0x40,0x20,0x10,
  0x08,0x08,0x00,0x00,0x08,0x14,0x08,0x00
};

CODE_BANK(KERNEL_BANK) static void testlib_preframe(void) {
  TIA.ctrlpf = PF_REFLECT;
  TIA.colubk = 0; // clear background
  TIA.pf0 = TIA.pf1 = TIA.pf2 = 0; // empty playfield
}

CODE_BANK(KERNEL_BANK) static void testlib_doframe(void) {
  const int nlines = 180;
  int i;
  char bgcolor;
  const char* pfmap;
  // Pass or fail?
  bool pass = test_has_result(true);
  bool fail = test_has_result(false);
  // Set color
  if (pass) {
    bgcolor = 0xc8;
    pfmap = PFMAP_GOOD;
  } else if (fail) {
    bgcolor = 0x48;
    pfmap = PFMAP_BAD;
  } else {
    bgcolor = 0x28;
    pfmap = PFMAP_UNKNOWN;
  }
  do_wsync();
  TIA.colubk = bgcolor;
  // Draw each scanline
  for (i=0; i<nlines/4; i++) {
    if (i >= 16 && i < 32) {
      do_wsync();
      TIA.pf1 = pfmap[i-16];
    } else {
      do_wsync();
    }
    do_wsync();
    do_wsync();
    do_wsync();
  }
}

CODE_BANK(KERNEL_BANK) static void testlib_postframe(void) {
  // additional post-frame processing goes here
}

// Display kernel loop
CODE_BANK(KERNEL_BANK) static void testlib_kernel_loop() {
    // loop forever
    while (1) {
      kernel_1();
      testlib_preframe();
      kernel_2();
      testlib_doframe();
      kernel_3();
      testlib_postframe();
      kernel_4();
    }
}

static void test_show_kernel() {
#ifdef MAPPER_BANKED_ROM
  banked_call_rom(KERNEL_BANK, testlib_kernel_loop);
#else
  testlib_kernel_loop();
#endif
}

void test_passed() {
  test_set_result(true);
  test_show_kernel();
}

void test_failed() {
  test_set_result(false);
  test_show_kernel();
}

// TODO: this would be nice but we can't spare two 2 RAM bytes for "jsr main"
// but maybe we can jmp _Exit (vs jsr _Exit)
/*
__attribute__((noreturn)) void _exit(int status) {
  test_failed();
  __builtin_unreachable();
}
*/
