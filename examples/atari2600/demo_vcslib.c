
#include <atari2600.h>
#include <vcslib.h>
#include <peekpoke.h>
#include <mapper.h>

#ifdef __ATARI2600_MAPPER_3E__
asm(".globl __cart_rom_size\n__cart_rom_size=8\n");
#endif

#if !defined(__ATARI2600__)
#error "This example is for Atari 2600 only"
#endif

unsigned char color; // a frame counter

#ifdef MAPPER_BANKED_ROM
#define ROM_BANK(index) __attribute__((noinline, section(".rom"#index)))
#else
#define ROM_BANK(index)
#endif

#define KERNEL_BANK 1

ROM_BANK(KERNEL_BANK) void my_preframe(void) {
  // Doing frame computation during blank
  // Update color
  TIA.colubk = color++; 
  // Set player 1 horizontal position
  set_horiz_pos(0, color >= 0x80 ? -color : color); 
  apply_hmove();
}

ROM_BANK(KERNEL_BANK) void my_doframe(void) {
  int i;
  char c = color;
  // Set player sprite color
  TIA.colup0 = COLOR_CONV(color);
  // Draw each scanline
  for (i=0; i<192; i++) {
    TIA.wsync = 0; // sync to scanline
    TIA.colubk = COLOR_CONV(c); // set background
    TIA.pf1 = i; // set playfield
    TIA.grp0 = i; // set sprite bitmap
    c++;
  }
  TIA.grp0 = 0; // clear sprite
}

ROM_BANK(KERNEL_BANK) void my_postframe(void) {
  // additional post-frame processing goes here
}

// Display kernel loop
ROM_BANK(KERNEL_BANK) void do_kernel_loop() {
    // loop until reset released
    while (SW_RESET()) { }
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

#ifdef MAPPER_XRAM

// XRAM on the VCS has different areas for read vs. write

typedef struct {
  char buf[256];
} XRAMStruct;

// XRAM on the VCS has different areas for read vs. write
// declare xram_data_read and xram_data_write as XRAM variables
DECLARE_XRAM_VARIABLE(0, XRAMStruct xram_data);

void test_ram(void) {
  char x;
  POKE(MAPPER_XRAM_WRITE | 0x7f0, 0xaa);
  x = PEEK(MAPPER_XRAM_READ | 0x3f0);
  if (x != 0xaa) asm("brk");
  xram_write(0x3f1, 0x55);
  x = xram_read(0x3f1);
  if (x != 0x55) asm("brk");
  xram_write(0x3f2, 0xaa);
  x = xram_read(0x3f2);
  if (x != 0xaa) asm("brk");
  xram_data_write.buf[0] = 1;
  x = xram_data_read.buf[0];
  if (x != 1) asm("brk");
}

#endif

int main() {

  // test extra RAM, if available
#ifdef MAPPER_XRAM  
  ram_select(0);
  test_ram();
#endif

  // test banked rom call, if available
#ifdef MAPPER_BANKED_ROM
  bank_select(KERNEL_BANK ^ 1);
  banked_call_rom(KERNEL_BANK, do_kernel_loop);
#else
  do_kernel_loop();
#endif
  
  return 0;
}
