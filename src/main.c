#define PPU_CTRL    *((unsigned char*)0x2000)
#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_STATUS  *((unsigned char*)0x2002)
#define PPU_SCROLL  *((unsigned char*)0x2005)
#define PPU_ADDR    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)

// Player variables
unsigned char player_x = 120;
unsigned char player_y = 120;

void wait_vblank() {
    while (!(PPU_STATUS & 0x80));
}

void main (void) {
    // 1. Turn off screen to load data
    PPU_MASK = 0x00; 
    
    // 2. Load a simple palette (Greens and Blues)
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = 0x01; // Background color (Dark Blue)

    // 3. Turn screen back on
    PPU_MASK = 0x1E; 

    while (1) {
        wait_vblank();
        
        // Game Logic: Gemini-style "Drift"
        player_x++; // The "Ghost" moves right automatically
        
        // Reset scroll to stop the screen from shaking
        PPU_SCROLL = 0x00;
        PPU_SCROLL = 0x00;
    }
}

