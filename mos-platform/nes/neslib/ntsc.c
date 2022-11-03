asm (".globl __do_init_ntsc_mode\n");
__attribute__((section(".zp.ntsc_mode"))) char NTSC_MODE;

char ppu_system(void) {
  return NTSC_MODE;
}
