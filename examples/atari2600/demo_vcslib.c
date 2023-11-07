
#include <atari2600.h>
#include <vcslib.h>
#include <peekpoke.h>

#if !defined(__ATARI2600__)
#error "This example is for Atari 2600 only"
#endif

unsigned char color;

void my_preframe(void) {
  // Doing frame computation during blank
  TIA.colubk = color++; // Update color
  set_horiz_pos(0, 80); // Set player 1
}

void my_doframe(void) {
  int i;
  char c = color;
  TIA.colup0 = COLOR_CONV(color);
  for (i=0; i<192; i++) {
    TIA.wsync = 0;
    TIA.colubk = COLOR_CONV(c);
    TIA.pf1 = i;
    TIA.grp0 = i;
    c++;
  }
  TIA.grp0 = 0;
}

void my_postframe(void) {
}

// Testing memory zones
const unsigned char rodata_v[] = "Hello!";
unsigned char data_v = 0x77;
unsigned char bss_v;

// Display kernel loop
#if defined(__ATARI2600_MAPPER__)
__attribute__((noinline, section(".rom1")))
#endif
void do_kernel_loop() {
    // loop until reset released
    while (SW_RESET()) { }
    // loop forever
    while (1) {
        // Vertical Sync signal
        TIA.vsync = 0x02;
        TIA.wsync = 0x00;
        TIA.wsync = 0x00;
        TIA.wsync = 0x00;
        TIA.vsync = 0x00;

        // Vertical Blank (preframe)
        RIOT.tim64t = VBLANK_TIM64;
        my_preframe();
        while (RIOT.intim != 0) {}

        TIA.wsync = 0x00;
        TIA.vblank = 0x00; // Turn on beam

        // Display frame (doframe)
#ifdef PAL
        RIOT.t1024t = KERNAL_T1024;
#else
        RIOT.tim64t = KERNAL_TIM64;
#endif
        my_doframe();
        while (RIOT.intim != 0) {}

        TIA.wsync = 0x00;
        TIA.vblank = 0x02; // Turn off beam

        // Overscan (postframe)
        RIOT.tim64t = OVERSCAN_TIM64;
        my_postframe();
        while (RIOT.intim != 0) {}

        // Test reset switch
        if (SW_RESET()) {
          asm("brk");
        }
    }
}

#if defined(__ATARI2600_MAPPER__)
void test_ram(void) {
  char x;
  POKE(0x17f0, 0xaa);
  x = PEEK(0x13f0);
  if (x != 0xaa) asm("brk");
  xram_write(0x3f1, 0x55);
  x = xram_read(0x3f1);
  if (x != 0x55) asm("brk");
  /*
  x = PEEK(&var); // 0xdeadbeef
  if (x != 0xef) asm("brk");
  */
}
#endif

int main() {

  #if __ATARI2600_MAPPER__ == 0x3e
  // for Stella detection
  asm("lda #0");
  asm("sta $3e");
  asm("sta $3f");
  asm("sta $3f");
  ram_select(0);
  test_ram();
  bank_select(0);
  banked_call_rom(1, do_kernel_loop);
  #else
  do_kernel_loop();
  #endif
  
  return 0;
}
