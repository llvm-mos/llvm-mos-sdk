// written by Doug Fraker
// version 1.2, 1/1/2022

__attribute__((section(".zp.vram_index"))) char VRAM_INDEX;

extern char VRAM_BUF[];

void set_vram_update(const void *buf);
void set_vram_buffer(void) {
  VRAM_BUF[0] = 0xff;
  VRAM_INDEX = 0;
  set_vram_update(VRAM_BUF);
}
