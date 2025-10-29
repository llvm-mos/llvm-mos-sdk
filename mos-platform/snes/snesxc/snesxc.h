#ifndef SLOWROM
#define SLOWROM ((uint8_t)0)
#endif

#ifndef FASTROM
#define FASTROM ((uint8_t)1)
#endif

//So if this isn't present vbcc optimizes out some register writes
//Such as, the kind that set the DMA's destination to be OAM
//instead of VRAM
#ifdef __VBCC__
#define FUNCTIONATR __noinline
#else
#define FUNCTIONATR
#endif

#ifndef _INITSNES
#define _INITSNES
void initSNES(uint8_t ROMSPEED);
FUNCTIONATR void LoadCGRam(const unsigned char *pSource, uint16_t pCGRAMDestination,
                uint16_t cSize);
FUNCTIONATR void LoadVram(const unsigned char *pSource, uint16_t pVRAMDestination, 
                uint16_t cSize);
FUNCTIONATR void LoadLoVram(const unsigned char *pSource, uint16_t pVRAMDestination,
                uint16_t cSize);
FUNCTIONATR void LoadHiVram(const unsigned char *pSource, uint16_t pVRAMDestination,
                uint16_t cSize);
FUNCTIONATR void ClearVram(const unsigned char *pSource, uint16_t pVRAMDestination,
                uint16_t cSize);
FUNCTIONATR void LoadOAMCopy(const unsigned char *pSource, uint16_t pVRAMDestination,
                uint16_t cSize);
void initOAMCopy(unsigned char *pSource);           

unsigned char* snesXC_getIRQ_ASM_Buffer(void);
#ifdef __VBCC__
unsigned char* snesXC_getIRQ_ASM_Buffer_vbcc(void);
#endif
void emitWAI(void);
void emitCLI(void);

void initSA1(void);

// Auto-enable 16-bit pointer mode for LLVM-MOS
#ifdef __mos__
#ifndef __SNESXC_16BIT_POINTERS__
#define __SNESXC_16BIT_POINTERS__
#endif
#endif

// For 16 bit mode code
// Banked memory copy copies data from ROM in another bank to LoRAM memory
void snesXC_memcpy_banked(void *dest, const void *src, size_t n);
void snesXC_setDataBank(uint8_t bankNum);

#endif // _INITSNES