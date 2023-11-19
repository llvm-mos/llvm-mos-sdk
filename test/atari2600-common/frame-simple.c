
#include <atari2600.h>
#include <vcslib.h>
#include <peekpoke.h>
#include <mapper.h>

#define KERNEL_BANK 1

/*{w:8,h:16}*/
RODATA_BANK(KERNEL_BANK) const char sprite_data[16] = {
  0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF,
  0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00
};

CODE_BANK(KERNEL_BANK) void my_preframe(void) {
}

CODE_BANK(KERNEL_BANK) void my_doframe(void) {
  int i;
  // Set player sprite color
  do_wsync(); // sync to scanline
  TIA.colup0 = COLOR_CONV(0xfe);
  // Draw each scanline
  for (i=0; i<191; i++) {
    do_wsync(); // sync to scanline
    TIA.colubk = i; // set background color
    TIA.pf1 = i; // set playfield
    TIA.grp0 = sprite_data[i & 15]; // set sprite bitmap
  }
  TIA.grp0 = 0; // clear sprite
  TIA.colubk = 0; // clear background
}

CODE_BANK(KERNEL_BANK) void my_postframe(void) {
  // additional post-frame processing goes here
}

// Display kernel loop
CODE_BANK(KERNEL_BANK) void do_kernel_loop() {
    // loop forever
    while (1) {
      kernel_1();
      my_preframe();
      kernel_2();
      my_doframe();
      kernel_3();
      my_postframe();
      kernel_4();
    }
}

int main() {

#ifdef MAPPER_BANKED_ROM
  banked_call_rom(KERNEL_BANK, do_kernel_loop);
#else
  do_kernel_loop();
#endif
  
  return 0;
}
