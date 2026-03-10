/* --- NES REGISTER DEFINITIONS --- */
#define PPU_CTRL    *((unsigned char*)0x2000)
#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_STATUS  *((unsigned char*)0x2002)
#define PPU_SCROLL  *((unsigned char*)0x2005)
#define PPU_ADDR    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)
#define OAM_DMA     *((unsigned char*)0x4014)
#define JOYPAD1     *((unsigned char*)0x4016)

/* --- GLOBAL VARIABLES --- */
unsigned char player_x = 120;
unsigned char player_y = 120;
unsigned char pads = 0;

/* --- HELPERS --- */
void wait_vblank() {
    while (!(PPU_STATUS & 0x80));
}

unsigned char read_joypad() {
    unsigned char i;
    unsigned char j = 0;
    JOYPAD1 = 1;
    JOYPAD1 = 0;
    for (i = 0; i < 8; ++i) {
        j = (j << 1) | (JOYPAD1 & 1);
    }
    return j;
}

/* --- MAIN GAME LOOP --- */
void main (void) {
    // Initialization
    PPU_MASK = 0x00; 
    
    // Set Background Palette to Dark Blue
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = 0x11; 
    
    // Set Sprite Palette to White
    PPU_ADDR = 0x3F; PPU_ADDR = 0x11;
    PPU_DATA = 0x30;

    PPU_MASK = 0x1E; // Enable rendering

    while (1) {
        wait_vblank();
        
        // Transfer sprite data from RAM ($0200) to PPU
        OAM_DMA = 0x02; 

        // Read Controller
        pads = read_joypad();

        // Move Sprite based on Input (Standard NES Controller bitmask)
        if (pads & 0x08) player_y++; // Down
        if (pads & 0x04) player_y--; // Up
        if (pads & 0x02) player_x--; // Left
        if (pads & 0x01) player_x++; // Right

        // Update Sprite 0 in RAM
        *((unsigned char*)0x0200) = player_y; // Y
        *((unsigned char*)0x0201) = 0x00;     // Tile
        *((unsigned char*)0x0202) = 0x00;     // Attributes
        *((unsigned char*)0x0203) = player_x; // X

        // Reset PPU scroll to prevent "screen shake"
        PPU_ADDR = 0x00; PPU_ADDR = 0x00;
        PPU_SCROLL = 0x00; PPU_SCROLL = 0x00;
    }
}
