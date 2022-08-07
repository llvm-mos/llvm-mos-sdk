#ifndef _NES_NROM_128_PPU_H_
#define _NES_NROM_128_PPU_H_

#ifdef __cplusplus
extern "C" {
#endif

void ppu_wait_vblank();
void ppu_write_addr(unsigned short addr);

#ifdef __cplusplus
}
#endif

#endif // not _NES_NROM_128_PPU_H_
