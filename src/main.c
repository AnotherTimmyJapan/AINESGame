#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_ADDR    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)

// Explicitly tell C that this function is in our ASM file
extern void __fastcall__ wait_vblank(void);

void main (void) {
    wait_vblank();
    
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = 0x11; // Blue

    PPU_MASK = 0x1E; 

    while (1) {
        wait_vblank();
    }
}
