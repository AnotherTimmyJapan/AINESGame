#include "nes_hw.h"

// Explicitly tell C that this function is in our ASM file
extern void __fastcall__ wait_vblank(void);

void main (void) {
    wait_vblank();
    
    // Using the clean names from our header
    PPU_ADDR = 0x3F; 
    PPU_ADDR = 0x00;
    PPU_DATA = 0x11; // Dark Blue

    PPU_MASK = 0x1E; // Show background and sprites

    while (1) {
        wait_vblank();
    }
}
