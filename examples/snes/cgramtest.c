#include <stdint.h>
#include <stddef.h>
#include <snes_regs_xc.h>

int main(void) {
    int8_t regRead1 = 0;
    uint8_t lastInputLo = 0;
    uint8_t lastInputHi = 0;
    REG_NMITIMEN = 0x01; //Joypad autoread enable
    REG_INIDISP = 0x0F; // Set brightness to 15, screen enabled
    for (;;) {
        do{ //Wait for Vblank
            regRead1 = REG_RDNMI;
        } while( (regRead1 > 0));
        do{ //Wait for joypad read ready
            regRead1 = REG_HVBJOY;
        } while( (regRead1 & 0x01) != 0);
        
        lastInputLo = REG_JOY1L;
        lastInputHi = REG_JOY1H;
        if (lastInputLo | lastInputHi) {
            REG_CGDATA = 0x1F;
            REG_CGDATA = 0x00;
            REG_CGADD = 0x00;
        }
        else {
            REG_CGDATA = 0x00;
            REG_CGDATA = 0x1F;
            REG_CGADD = 0x00;
        }
    }
}
