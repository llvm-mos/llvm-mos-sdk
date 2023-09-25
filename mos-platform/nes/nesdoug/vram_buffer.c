// written by Doug Fraker
// version 1.2, 1/1/2022

__attribute__((section(".zp.vram_index"))) char VRAM_INDEX;

extern char VRAM_BUF[128];

__attribute__((leaf)) void __post_vram_update();

void set_vram_update(const void *buf);
void set_vram_buffer(void) {
  set_vram_update(VRAM_BUF);
  __post_vram_update();
}
