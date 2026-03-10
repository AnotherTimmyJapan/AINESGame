#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_ADDR    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)

// We call the assembly version of wait_vblank now for better stability
extern void wait_vblank(void);

void main (void) {
    // 1. Initialize Palette
    wait_vblank();
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = 0x11; // Blue background

    // 2. Enable Graphics
    PPU_MASK = 0x1E; 

    while (1) {
        wait_vblank();
        // Just keep the lights on
    }
}
