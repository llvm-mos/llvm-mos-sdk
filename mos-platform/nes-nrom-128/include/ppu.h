#ifndef _NES_NROM_128_PPU_H_
#define _NES_NROM_128_PPU_H_

#ifdef __cplusplus
extern "C" {
#endif

// PPU registers
extern volatile char PPUCTRL;
extern volatile char PPUMASK;
extern volatile char PPUSTATUS;
extern volatile char OAMADDR;
extern volatile char OAMDATA;
extern volatile char PPUSCROLL;
extern volatile char PPUADDR;
extern volatile char PPUDATA;

// CPU OAM DMA port
extern volatile char OAMDMA;

void ppu_wait_vblank();
void ppu_write_addr(unsigned short addr);

#ifdef __cplusplus
}
#endif

#endif // not _NES_NROM_128_PPU_H_
