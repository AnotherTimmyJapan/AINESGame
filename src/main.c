#include "nes_hw.h"

extern void __fastcall__ wait_vblank(void);

unsigned char px = 128; // Player X
unsigned char py = 120; // Player Y

void main (void) {
    wait_vblank();

    // 1. Set Palette
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = 0x11; // Blue Background
    PPU_ADDR = 0x3F; PPU_ADDR = 0x11;
    PPU_DATA = 0x30; // White Sprite Color

    // 2. Enable Graphics
    PPU_MASK = 0x1E; 

    while (1) {
        wait_vblank();

        // 3. Move the player (drift for now to test)
        px++;

        // 4. Update Sprite 0 in OAM (Memory $0200)
        *((unsigned char*)0x0200) = py;   // Y-axis
        *((unsigned char*)0x0201) = 0x00; // Tile Index (Tile 0 we made)
        *((unsigned char*)0x0202) = 0x00; // Attributes
        *((unsigned char*)0x0203) = px;   // X-axis

        // 5. Trigger DMA (Transfer RAM $0200 to PPU)
        OAM_DMA = 0x02;

        // Reset Scroll
        PPU_ADDR = 0x00; PPU_ADDR = 0x00;
        PPU_SCROLL = 0x00; PPU_SCROLL = 0x00;
    }
}
